#include "../../include/minishell.h"

// int	ft_export(t_command *command, t_env **env_list)
// {
// 	    t_env   *current;
//     size_t  str_len;
//     size_t  index;

//     current = *env_list;
//     index = 1;
//     if(!command->args[1])
// 	{
//         ft_putstr_fd("export: not enough arguments\n", 1);
// 		return (ERROR);
// 	}
//     while(command->args[index])
//     {
// 		add_export_to_env
//         index++;
//     }
//     return (SUCCESS);
// }