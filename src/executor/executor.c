#include "../../include/minishell.h"

int	executor(t_shell *shell)
{
    if (!shell->command)
        return(ERROR);
    if (check_if_builtin(shell->command->args[0]) == TRUE)
    {
		if(execute_builtin(shell) == 1)
			return(ERROR);
		ft_putstr_fd("ft builtin executed\n", 1);
    }
    else if (!shell->command->next)
        handle_single_command(shell);
    else
        handle_multiple_commands(shell);
	return (SUCCESS);
}