#include "../../include/minishell.h"

void ft_env(t_shell *shell, t_command *command)
{
    if (command->args[1])
        return (shell_error(shell, env_error, command->args[0], 127));
    print_environment(shell->environment);
}