# include "../../include/minishell.h"

void	print_list_env(t_env *env_list)
{

	if(env_list == NULL)
		exit(EXIT_FAILURE);
	while (env_list)
	{
		ft_putstr_fd(env_list->name, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(env_list->value, 1);
		ft_putchar_fd('\n', 1);
		env_list = env_list->next;
	}
}

static t_env	*search_last_node_env(t_env *env_list) 
{
    if (!env_list) 
        return (NULL);
    while (env_list->next)
        	env_list = env_list->next;
    return (env_list);
}

void	add_node_to_list_env(t_env **env_list, t_env *new_node)
{
	t_env	*last_node;

	if (!*env_list)
	{
		*env_list = new_node;
		return ;
	}
	last_node = search_last_node_env(*env_list);
	last_node->next = new_node;
}

char *env_get_var_value(t_shell *shell, char *var)
{
	t_env	*temp;
	size_t	len;

	if (!var)
		return (NULL);
	len = ft_strlen(var);
	temp = shell->env_list;
	while (temp)
	{
		if (ft_strncmp(var, temp->name, len) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

void	env_set_var_value(t_shell *shell, char *name, char *value)
{
	t_env	*temp;
	t_env	*new;
	size_t	len;

	if (!name)
		return ;
	len = ft_strlen(name);
	temp = shell->env_list;
	while (temp)
	{
		if (ft_strncmp(name, temp->name, len) == 0)
		{
			free(temp->value);
			temp->value = value;
			return ;
		}
		temp = temp->next;
	}
	new = ft_calloc(1, sizeof(t_env));
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	add_node_to_list_env(&(shell->env_list), new);
	if (!new || !new->name || !new->value)
		return (shell_error(shell, malloc_error, "env_set_var_value()", 1));
}
