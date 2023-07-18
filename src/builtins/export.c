#include "../../include/minishell.h"

int	add_export_to_env(char *args, t_env **env_list)
{
	t_env	*new_node;

		new_node = create_new_node(args);
		if(!new_node)
		{
			// free_list_env(shell->env_list); remove node in unset function
			return(FAILED);
		}
		add_node_to_list_env(env_list, new_node);
	return(SUCCESS);
}

int	ft_export(t_command *command, t_env **env_list)
{
	t_env   *current;
    size_t  index;

    current = *env_list;
    index = 1;
    if(!command->args[1])
	{
        ft_putstr_fd("export: not enough arguments\n", 1);
		return (ERROR);
	}
    while(command->args[index])
    {
		if(add_export_to_env(command->args[index], env_list))
			return(FAILED);
        index++;
    }
    return (SUCCESS);
}