#include "../../include/minishell.h"

#define HEREDOC_PROMPT "> "


static void	put_line_fd(char *line, int fd_write_end)
{
	ft_putstr_fd(line, fd_write_end);
	ft_putstr_fd("\n", fd_write_end);
}

int	ft_here_doc(char *delimiter, int fd_write_end)
{
	char	*line;

	if (!delimiter || !(*delimiter))
		return (ERROR);
	// signal(SIGINT, signal_ctrl_c_heredoc);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("heredoc line failed", 1);
			exit(EXIT_FAILURE);
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		put_line_fd(line, fd_write_end);
		free(line);
	}
	return (SUCCESS);
}
