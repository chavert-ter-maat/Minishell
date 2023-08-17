/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_here_doc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/17 13:37:09 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/17 13:52:11 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_heredoc(t_shell *shell)
{
	t_node		*command_node;
	t_command	*command;
	t_node		*redir_node;

	command_node = shell->command_list->head;
	while (command_node)
	{
		command = command_node->data;
		redir_node = command->redir_list->head;
		while (redir_node)
		{
			if (check_redir_type2(redir_node->data) == HEREDOC)
				create_here_doc(shell, redir);
			redir_node = redir_node->next;
		}
		command_node = command_node->next;
	}
}
