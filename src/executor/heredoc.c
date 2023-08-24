#include "../../include/minishell.h"

static void	here_wait(t_shell *shell, pid_t pid, int status)
{
	if (waitpid(pid, &status, 0) == FAILED)
		perror_exit_fork(shell, "waitpid");
	if (WIFSIGNALED(status))
		shell->status = g_status;
	else
		shell->status = WEXITSTATUS(status);
}

static void	sigint_handler_heredoc(int signum)
{
	(void) signum;
	_exit(1);
}

static void	init_signals_heredoc(void)
{
	signal(SIGINT, &sigint_handler_heredoc);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

static void	write_to_pipe(t_shell *shell, char *delimiter, int pipe_fd)
{
	char	*line;

	line = readline("> ");
	while (line && !(ft_strncmp(line, delimiter,
				ft_strlen(delimiter) + 1) == 0))
	{
		write(pipe_fd, line, ft_strlen(line));
		write(pipe_fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (line)
		free (line);
	if (close(pipe_fd) == FAILED)
		perror_exit_fork(shell, "close");
	_exit(0);
}

void	create_heredoc(t_shell *shell, t_redir *redir)
{
	int		status;
	int		pipe_fd[2];
	pid_t	pid;

	status = 0;
	if (redir->heredoc_read_end)
		close(redir->heredoc_read_end);
	if (!redir->file || redir->file[0] == '\0')
		return (perror_update_status(shell, "close"));
	if (pipe(pipe_fd) == FAILED)
		return (perror_update_status(shell, "pipe"));
	pid = fork();
	if (pid == FAILED)
		return (perror_update_status(shell, "fork"));
	if (pid == SUCCESS)
	{
		init_signals_heredoc();
		write_to_pipe(shell, redir->file, pipe_fd[WRITE_END]);
	}
	if (close(pipe_fd[WRITE_END]) == FAILED)
		perror_exit_fork(shell, "close");
	here_wait(shell, pid, status);
	redir->heredoc_read_end = pipe_fd[READ_END];
}