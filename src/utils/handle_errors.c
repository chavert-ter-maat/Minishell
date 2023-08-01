#include "../../include/minishell.h"


//set errno?
void	perror_exit(t_shell *shell, char *input)
	{
		ft_putstr_fd("Shell_yeah: ", STDERR_FILENO);
		perror(input);
		ft_exit(shell, EXIT_FAILURE);
	}

void	error_no_command(t_shell *shell, char *cmd)
{
	(void) shell;
	ft_putstr_fd("Shell_yeah: ", STDERR_FILENO);
	if(cmd != NULL)
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("command not found\n", STDERR_FILENO);
	// ft_exit(shell, EXIT_FAILURE);
	_exit(1);
	
}
