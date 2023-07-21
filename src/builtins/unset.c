#include "../../include/minishell.h"

void    free_node(t_env *current)
{
	free(current->name);
	free(current->value);
	free(current);
}
void remove_node(t_env **env_list, t_env *current)
{
	t_env *temp = *env_list;

    if (*env_list == current) 
        *env_list = current->next;
    else 
	{
        while (temp && temp->next != current) 
            temp = temp->next;
        temp->next = current->next;
    }
    free_node(current);
}

int ft_unset(t_command *command, t_env **env_list)
{
	t_env	*current;
	size_t 	strlen;
	size_t	index;

	current = *env_list;
	index = 1;
	if(!command->args[1])
	{
		ft_putstr_fd("unset: not enough arguments\n", 1);
		return (ERROR);
	}
	while(command->args[index])
	{
		strlen = ft_strlen(command->args[index]) + 1;
		while(current)
		{
			if(ft_strncmp(current->name, command->args[index], strlen) == 0)
			{
				remove_node(env_list, current);
				return (SUCCESS);
			}
			current = current->next;
		}
		index++;
	}
	return (ERROR);
}
