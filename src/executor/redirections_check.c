/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections_check.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/23 17:00:45 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/08/23 18:14:35 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_redir(t_shell *shell, t_command *command,
		t_redir *redir, pid_t pid)
{
	if (redir->type == IN)
		return (redir_in(shell, redir->file, command, pid));
	if (redir->type == OUT)
		return (redir_out(shell, redir->file, command, pid));
	if (redir->type == HEREDOC)
		return (redir_heredoc(shell, command, redir, pid));
	if (redir->type == APPEND)
		return (redir_append(shell, redir->file, command, pid));
}

void	handle_redirection(t_shell *shell, t_command *command, pid_t pid)
{
	t_node	*node;

	node = command->redir_list->head;
	while (node)
	{
		handle_redir(shell, command, node->data, pid);
		node = node->next;
	}
}
