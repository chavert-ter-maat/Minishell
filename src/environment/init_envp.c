#include "../../include/minishell.h"

char	*get_envp_name(char *new_envp_variable)
{
	char	*name;
	int		index;

	index = 0;
	if(!new_envp_variable)
		return(NULL);
	while (new_envp_variable[index] && new_envp_variable[index] != 0)
		index++;
	name = ft_substr(new_envp_variable, 0, index);
	if(!name)
		return(NULL);
	return(name);
}
char	*get_envp_variable(char *new_envp_variable)
{
	char	*variable;
	int		start;
	int		end;

	start = 0;
	end = 0;
	if(!new_envp_variable)
		return(NULL);
	while(new_envp_variable[start] != 0)
		start++;
	while (new_envp_variable[end])
		end++;
	variable = ft_substr(new_envp_variable, start, end);
	if(!variable)
		return(NULL);
	return(variable);
}

t_envp	*create_new_node(char *new_envp_variable)
{
	t_envp	*new_node;

	new_node = ft_calloc(new_node, sizeof(char));
	if (!new_node)
	{
		ft_printf ("Malloc failed"),
		exit (EXIT_FAILURE);
	}
	new_node->name = get_envp_name(new_envp_variable);
	if(!new_node->name)
		exit();
	new_node->value = get_envp_value();
		exit();
	new_node->next = NULL;
	return (new_node);

}

int	init_envp(t_shell *shell, char **envp)
{
	t_envp	*envp_list;
	t_envp	*new_node;
	int		index;

	index = 0;
	envp_list = NULL;
	while(envp[index])
	{
		new_node = create_new_node(envp[index]);
		if(!new_node)
			free_list(envp_list);
		add_node_to_list(&envp_list, new_node);
		index++;
	}
}