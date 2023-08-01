#include "../../include/minishell.h"

void	ft_exit(t_shell *shell, int exitstatus)
{
	shell->environment = free_list(shell->environment);
	free_shell(shell);
	ft_putstr_fd("test exit", 1);
	exit(exitstatus);
}
