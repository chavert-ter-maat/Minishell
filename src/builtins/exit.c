#include "../../include/minishell.h"


void	clean_exit(t_shell *shell)
{
	shell->environment = free_list(shell->environment);
	free_shell(shell);
	_exit(shell->return_value);
}

static bool	numeric(char *str)
{
	size_t	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit(t_shell *shell, t_command *command)
{
	ft_putstr_fd("exit\n", 1);
	if (command->arg_list->count == 1)
	{
		shell->return_value = 0;
		clean_exit(shell);
	}
	if (numeric(command->args[1]) == false)
	{
		shell_error(shell, exit_numeric_arg, command->args[1], 255);
		clean_exit(shell);
	}
	if (command->arg_list->count > 2)
	{
		shell_error(shell, too_many_args, "exit", 1);
		return ;
	}
	else
	{
		shell->return_value = ft_atoi(command->args[1]) % 256;
		if (shell->return_value < 0)
			shell->return_value += 256;
		clean_exit(shell);
	}
}
