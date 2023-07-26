#include "../../include/minishell.h"

void	ft_exit(t_shell *shell)
{
	shell->environment = free_list(shell->environment);
	free_shell(shell);
	exit(SUCCESS);
}
