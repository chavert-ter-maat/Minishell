#include "../../include/minishell.h"

void ft_unset(t_shell *shell, t_command *command)
{
	t_node	*target;
	size_t	index;

	if(!command->args[1])
	{
		shell_error(shell, argc_error, "unset", 1); //return value 1??????
		return ;
	}
	index = 1;
	while(command->args[index])
	{
		target = list_get_node(shell->environment, command->args[index++]);
		if (target)
			list_remove_node(shell->environment, target);
	}
}
