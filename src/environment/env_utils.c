# include "../../include/minishell.h"

void	print_list_env(t_env *env_list)
{

	if(env_list == NULL)
		exit(EXIT_FAILURE);
	while (env_list)
	{
		ft_printf("%s", env_list->name);
		ft_printf("%s\n", env_list->value);
		env_list = env_list->next;
	}
}

void	free_list_env(t_env *env_list)
{
	t_env	*temp;
	if (!env_list)
		return ;
	while (env_list)
	{
		temp = (env_list)->next;
		free(env_list);
		env_list = temp;
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

