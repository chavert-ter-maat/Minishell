#include "../../include/minishell.h"

static int  get_argc(t_command *cmd)
{
    int			i;
	t_argument	*temp;

	i = 0;
	if (cmd->arg_list)
	{
		temp = cmd->arg_list;
		i = 1;
		while (temp)
		{
			temp = temp->next;
			i++;
		}
	}
    return (i);
}

char	**arg_list_to_array(t_command *cmd)
{
	int			i;
	t_argument	*temp;
	char		**args;

    i = get_argc(cmd);
	args = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	if (cmd->arg_list)
	{
		temp = cmd->arg_list;
		while (temp)
		{
			args[i] = temp->str;
			temp = temp->next;
			i++;
		}
	}
    return (args);
}
