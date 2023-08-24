/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/17 13:39:24 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/24 17:12:58 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	skip_space(t_node **node)
{
	t_token	*token;

	if (!*node)
		return ;
	token = (t_token *)(*node)->data;
	while (token && token->type == E_SPACE)
	{
		*node = (*node)->next;
		if (*node)
			token = (t_token *)(*node)->data;
		else
			return ;
	}
}

char	**arg_list_to_array(t_shell *shell, t_command *command)
{
	char	**args;
	char	**arg;
	t_node	*temp;
	int		i;

	args = ft_calloc(command->arg_list->count + 1, sizeof(char *));
	if (!args)
		return (shell_error(shell, malloc_error, "arg_list_to_array", 1), NULL);
	i = 0;
	if (args && command->arg_list)
	{
		temp = command->arg_list->head;
		while (temp)
		{
			arg = (char **) temp->data;
			if (i == 0)
				ft_strtolower(*arg);
			args[i] = *arg;
			temp = temp->next;
			i++;
		}
	}
	return (args);
}
