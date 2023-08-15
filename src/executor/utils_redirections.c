#include "../../include/minishell.h"

void	change_fd_to_in(int fd)
{
	if (dup2(fd, STDIN_FILENO) == FAILED)
	{
		ft_putstr_fd ("fix error function", 1); 
		_exit (1);
	}
	if (close (fd) == FAILED)
	{
		ft_putstr_fd ("fix error function", 1); 
		_exit (1);
	}
}



void	change_fd_to_out(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == FAILED)
	{
		ft_putstr_fd ("fix error function", 1); 
		_exit(1);
	}
	if (close(fd) == FAILED)
	{
		ft_putstr_fd("fix error function", 1); 
		_exit (1);
	}
}