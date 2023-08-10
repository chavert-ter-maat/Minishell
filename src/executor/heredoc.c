#include "../../include/minishell.h"

void	handle_here_doc(t_shell *shell, t_command *command, char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	if (!delimiter || !(*delimiter))
		return(shell_error(shell, syntax_error, "\\n", NULL, 139));
	if (pipe(pipe_fd) == FAILED)
	{
		ft_putstr_fd("heredoc line failed", 1);
		exit(EXIT_FAILURE); //check for right exit!!!!
	}
	line = readline("> ");
	while (line && !(ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0))
	{
	// signal(SIGINT, signal_ctrl_c_heredoc);	check for signals!!
		write(pipe_fd[WRITE_END], line, ft_strlen(line));
		write(pipe_fd[WRITE_END], "\n", 1);
		free(line);
		line = readline("> ");
	}
	if(line)
		free(line);
	close(pipe_fd[WRITE_END]);
	command->read_fd = pipe_fd[READ_END];
}
	