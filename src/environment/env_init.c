#include "../../include/minishell.h"

char	*get_env_name(char *new_env_variable)
{
	char	*name;
	int		index;

	index = 0;
	while (new_env_variable[index] && new_env_variable[index] != '=')
		index++;
	name = ft_substr(new_env_variable, 0, (index));
	if(!name)
		return(NULL);
	return(name);
}
char	*get_env_value(char *new_env_variable)
{
	char	*variable;
	int		start;
	int		end;

	start = 0;
	end = 0;
	while(new_env_variable[start] && new_env_variable[start] != '=')
		start++;
	while (new_env_variable[end])
		end++;
	variable = ft_substr(new_env_variable, (start + 1), (end - 1)); //checken end -1
	if(!variable)
		return(NULL);
	return(variable);
}

t_env	*create_new_node(char *new_env_variable)
{
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
	{
		ft_printf ("Calloc failed"),
		exit (EXIT_FAILURE);
	}
	new_node->name = get_env_name(new_env_variable);
	if(!new_node->name)
		exit(EXIT_FAILURE);
	new_node->value = get_env_value(new_env_variable);
	if(!new_node->value)
		exit(EXIT_FAILURE);
	new_node->next = NULL;
	return (new_node);
}

t_env	*init_env(char **envp)
{
	t_env	*new_node;
	t_env	*env_list;
	int		index;

	index = 0;
	env_list = 	NULL;
	while(envp[index])
	{
		new_node = create_new_node(envp[index]);
		if(!new_node)
			free_list_env(env_list);
		add_node_to_list_env(&env_list, new_node);
		index++;
	}
	return(env_list);
}