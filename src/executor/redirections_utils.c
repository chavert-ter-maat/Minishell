/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:03:57 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/16 15:04:33 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_redir_type2(t_redir *redir)
{
	if (!redir)
		return (NOT_FOUND);
	if (redir->type == IN)
		return (IN);
	if (redir->type == OUT)
		return (OUT);
	if (redir->type == HEREDOC)
		return (HEREDOC);
	if (redir->type == APPEND)
		return (APPEND);
	return (NOT_FOUND);
}

int	check_redir_type(t_command *command)
{
	t_node	*node;
	int		redir_type;

	redir_type = NOT_FOUND;
	if (!command || !command->redir_list)
		return (redir_type);
	node = command->redir_list->head;
	while (node)
	{
		redir_type = check_redir_type2(node->data);
		node = node->next;
	}
	return (redir_type);
}
