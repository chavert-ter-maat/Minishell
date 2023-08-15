#include "../../include/minishell.h"

int g_status;

void    init_shell(t_shell *shell, char **envp)
{

	ft_bzero(shell, sizeof(t_shell));
    g_status = 0;
    init_env(shell, envp);
}
