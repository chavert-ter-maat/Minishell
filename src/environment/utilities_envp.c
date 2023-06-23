# include "../../include/minishell.h"

void	print_list_envp(t_envp *envp_list)
{
	while (envp_list)
	{
		ft_printf("%s = ", envp_list->name);
		ft_printf("%s\n", envp_list->value);
		envp_list = envp_list->next;
	}
}

// int	count_nodes(t_envp *envp_list)
// {
// 	int		amount;

// 	amount = 0;
// 	while (envp_list)
// 	{
// 		amount++;
// 		envp_list = envp_list->next;
// 	}
// 	return (amount);
// }

void	free_list_envp(t_envp **envp_list)
{
	t_envp	*temp;

	if (!envp_list)
		return ;
	while (*envp_list)
	{
		temp = (*envp_list)->next;
		free(*envp_list);
		*envp_list = temp;
	}
}

static t_envp	*search_last_node(t_envp *envp_list)
{
	if (!envp_list)
		return (0);
	while (envp_list->next)
		envp_list = envp_list->next;
	return (envp_list);
}

void	add_to_list(t_envp **envp_list, t_envp *new_node)
{
	t_envp	*last_node;

	if (!*envp_list)
	{
		*envp_list = new_node;
		return ;
	}
	last_node = search_last_node(*envp_list);
	last_node->next = new_node;
}