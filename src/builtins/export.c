#include "../../include/minishell.h"

void	ft_export(t_shell *shell, t_command *command)
{
    size_t  index;

    index = 1;
    if(!command->args[1])
		return (shell_error(shell, argc_error, "export", 1)); //return value 1 ?????????
    while(command->args[index])
    {
		if (add_var_to_environment(shell, command->args[index++]) != 0)
			return ;
    }
}