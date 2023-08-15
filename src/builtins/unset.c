#include "../../include/minishell.h"

void	ft_unset(t_shell *shell, t_command *command)
{
	t_node	*target;
	size_t	index;
	t_var	*var;

	if (!command->args[1])
	{
		shell_error(shell, too_little_args, "unset", NULL, 1);
		return ;
	}
	index = 1;
	while (command->args[index])
	{
		target = list_get_node(shell->environment, command->args[index++]);
		if (target)
		{
			var = (t_var *) target->data;
			list_remove_node(shell->environment, var->name);
		}
	}
	g_status = 0;
}
