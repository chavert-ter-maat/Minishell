#include "../../include/minishell.h"

void	handle_here_doc(t_shell *shell, char *delimiter, char *flag)
{
	int		pipe_fd[2];
	char	*line;

	if (!delimiter || !(*delimiter))
		return(shell_error(shell, syntax_error, "\\n", NULL, 139));
	if (pipe(pipe_fd) == FAILED)
	{
		perror_return_promt("pipe"); //check for right exit!!!!
		return ;
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
	ft_putstr_fd("komt ie hier in heredoc?\n", 1);
	if(ft_strncmp("YES_COMMAND", flag, 12) == 0)
		change_fd_to_in(pipe_fd[READ_END]);
}
	