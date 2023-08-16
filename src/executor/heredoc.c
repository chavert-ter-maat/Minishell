#include "../../include/minishell.h"

void	handle_here_doc(t_shell *shell, t_command *command, char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	if (!delimiter || !(*delimiter))
		return (shell_error(shell, syntax_error, "\\n", NULL, 139));
	if (pipe(pipe_fd) == FAILED)
		return (perror_return_promt("pipe")); //check for right exit!!!!
	line = readline("> ");
	while (line && !(ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0))
	{
		write(pipe_fd[WRITE_END], line, ft_strlen(line));
		write(pipe_fd[WRITE_END], "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (line)
		free (line);
	if (close(pipe_fd[WRITE_END]) == FAILED)
	{
		ft_putstr_fd ("fix error function", 1); 
		_exit (1);
	}
	if (command->arg_list->count > 0)
		change_fd_to_in(pipe_fd[READ_END]);
}

	