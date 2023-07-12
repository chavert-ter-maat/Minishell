#include "../../include/minishell.h"

static void	env_error_message(char *message)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
}
int	ft_env(t_shell *shell)
{
	if (shell->command->args[1])
	{
		shell->return_value = 127;
		env_error_message(shell->command->args[1]);
		return(FAILED);
	}
	print_list_env(shell->env_list);
	return(SUCCESS);
}