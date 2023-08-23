/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:06:17 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/23 13:34:31 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*note to self: dit werkt nu alleen in een child proces..
HOe fix ik dat dit altijd werkt? en exit code is ook gek.
is signal(SIGINT, SIG_DFL) niet t zelfde?
*/

// static void	here_wait(t_shell *shell, pid_t pid, int status)
// {
// 	if (waitpid(pid, &status, 0) == FAILED)
// 		perror_exit_fork(shell, "waitpid");
// 	if (WIFSIGNALED(status))
// 		shell->status = g_status;
// 	else
// 		shell->status = WEXITSTATUS(status);
// }

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
	// _exit(0);
}

void	create_heredoc(t_shell *shell, t_redir *redir)
{
	// pid_t	pid;
	int		pipe_fd[2];
	int		status;
	
	status = 0;
	if (!redir->file || redir->file[0] == '\0')
		return (shell_error(shell, syntax_error, "\\n", 139));
	if (pipe(pipe_fd) == FAILED)
		return (perror_update_status(shell, "pipe"));
	// pid = fork();
	// if (pid == FAILED)
	// 	return (perror_update_status(shell, "fork"));
	// if (pid == SUCCESS)
	// {
		init_signals_heredoc();
		write_to_pipe(shell, redir->file, pipe_fd[WRITE_END]);
	// }
	redir->heredoc_read_end = pipe_fd[READ_END];

	// here_wait(shell, pid, status);
	// if (waitpid(pid, &status, 0) == FAILED)
	// 	perror_exit_fork(shell, "waitpid");
	// if (WIFSIGNALED(status))
	// 	shell->status = g_status;
	// else
	// 	shell->status = WEXITSTATUS(status);
	// printf("after wait\n");
}
