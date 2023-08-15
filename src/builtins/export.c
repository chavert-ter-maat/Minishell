#include "../../include/minishell.h"

static void	print_export(t_shell*shell)
{
	t_node	*temp;
	t_var	*var;

	if (!shell->environment | !shell->environment->head)
		return ;
	temp = shell->environment->head;
	while (temp)
	{
		var = (t_var *) temp->data;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(var->name, 1);
		if (var->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(var->value, 1);
			ft_putendl_fd("\"", 1);
		}
		else
			ft_putchar_fd('\n', 1);
		temp = temp->next;
	}
}

void	ft_export(t_shell *shell, t_command *command)
{
	size_t	index;

	index = 1;
	if (!command->args[1])
	{
		g_status = 0;
		return (print_export(shell));
	}
	while (command->args[index])
	{
		if (add_var_to_environment(shell, command->args[index++]) != 0)
		{
			g_status = 1;
			return;
		}
	}
	g_status = 0;
}
