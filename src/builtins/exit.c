#include "../../include/minishell.h"

void	ft_exit(t_shell *shell)
{
	free_env_list(&(shell->env_list));
	free_shell(shell);
	exit(SUCCESS);
}
