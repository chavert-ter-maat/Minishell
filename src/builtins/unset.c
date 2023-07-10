#include "../../include/minishell.h"

void	free_node(t_env *current)
{
	if(current->name)
		free(current->name);
	if(current->value)
		free(current->value);
	free(current);
}

void	remove_node(t_env **env_list, t_command *current)
{
	t_env	*temp;

	temp = env_list;
	while(temp->next != current)
		temp = temp->next;		
	temp->next = current->next;
	free_node(current);
}

// what if no variable?
void	ft_unset(t_command *command, t_env **env_list)
{
	t_env	*current;
	size_t	str_len;
	size_t	index;

	current = env_list;
	index = 0;
	if(!command->args[0])
	{
		ft_putstr_fd("input name", 1);
		exit(EXIT_FAILURE);
	}
	while(command->args[index])
	{
		str_len = ft_strlen(command->args[index]);
		while(current && current->next)
		{
			if(ft_strncmp(current->name, command->args[index], str_len))
				remove_node(&env_list, current);
			current = current->next;
		}
		index++;
	}
}
