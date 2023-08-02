# include "../../include/minishell.h"

void	print_environment(t_list *environment)
{
	t_node	*temp;
	t_var	*var;

	if(!environment | !environment->head)
		return ;
	temp = environment->head;
	while (temp)
	{
		var = (t_var *) temp->data;
		if (var->value)
		{
			ft_putstr_fd(var->name, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(var->value, 1);
			ft_putchar_fd('\n', 1);
		}
		temp = temp->next;
	}
}

char *env_get_var_value(t_shell *shell, char *name)
{
	t_node	*target;
	t_var	*var;

	if (!shell->environment || !shell->environment->head || !name)
		return (NULL);
	target = list_get_node(shell->environment, name);
	if (!target)
		return (NULL);
	var = (t_var *) target->data;
	return (var->value);
}

static void	env_add_new_var(t_shell *shell, char *name, char *value)
{
	t_var	new_var;

	new_var.name = name;
	new_var.value = value;
	list_add_new_node(shell, shell->environment, &new_var);
}

void	env_set_var_value1(t_shell *shell, char *name, char *value)
{
	t_node	*target;
	t_var	*var;

	if (!name || !shell->environment)
		return ;
	target = list_get_node(shell->environment, name);
	if (!target)
		return (env_add_new_var(shell, name, value));
	var = (t_var *) target->data;
	if (var->value)
		free(var->value);
	free(name);
	var->value = value;
}

void	env_set_var_value2(t_shell *shell, char *not_allocated_name, char *value)
{
	t_node	*target;
	t_var	*var;
	char	*name;

	if (!not_allocated_name || !shell->environment || !shell->environment->head)
		return ;
	target = list_get_node(shell->environment, not_allocated_name);
	if (!target)
	{
		name = ft_strdup(not_allocated_name);
		if (!name)
		{
			free(value);
			return(shell_error(shell, malloc_error, "env_set_var_value2", 1));
		}
		env_add_new_var(shell, name, value);
		return ;
	}
	var = (t_var *) target->data;
	if (var->value)
		free(var->value);
	var->value = value;
}