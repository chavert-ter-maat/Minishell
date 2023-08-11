#include "../../include/minishell.h"

void	handle_here_doc(t_shell *shell, t_command *command, char *delimiter, char *f)
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
		write(pipe_fd[WRITE_END], line, ft_strlen(line));
		write(pipe_fd[WRITE_END], "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (line)
		free (line);
	close (pipe_fd[WRITE_END]);
	command->read_fd = pipe_fd[READ_END];
	int check = 0;
	if(ft_strncmp("YES_COMMAND", f, 12) == 0)
	{
	
		if (dup2(command->read_fd, STDIN_FILENO) == FAILED)
		{
			ft_putstr_fd ("fix error function", 1); 
			_exit(1);
		}
		if (close(command->read_fd) == FAILED)
		{
			ft_putstr_fd("fix error function", 1); 
			_exit (1);
		}
	}
}
	