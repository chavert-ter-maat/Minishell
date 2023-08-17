/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:04:12 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/17 15:14:30 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	redir_heredoc(t_shell *shell, t_command *command, t_redir *redir)
{
	if (command->arg_list->count > 0)
		change_fd_to_in(shell, redir->heredoc_read_end);
}

static void	redir_in(t_shell *shell, char *file, t_command *command)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == FAILED)
		perror_exit_fork(shell, "open");
	if (command->arg_list->count > 0)
		change_fd_to_in(shell, fd);
}

// redirects stfout to file
static void	redir_out(t_shell *shell, char *file, t_command *command)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == FAILED)
		perror_exit_fork(shell, "open");
	if (command->arg_list->count > 0)
		change_fd_to_out(shell, fd);
}

static void	redir_append(t_shell *shell, char *file, t_command *command)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == FAILED)
		perror_exit_fork(shell, "open");
	if (command->arg_list->count > 0)
		change_fd_to_out(shell, fd);
}

static void	handle_redir(t_shell *shell, t_command *command,
		t_redir *redir)
{
	if (redir->type == IN)
		return (redir_in(shell, redir->file, command));
	if (redir->type == OUT)
		return (redir_out(shell, redir->file, command));
	if (redir->type == HEREDOC)
		return (redir_heredoc(shell, command, redir));
	if (redir->type == APPEND)
		return (redir_append(shell, redir->file, command));
}

void	handle_redirection(t_shell *shell, t_command *command)
{
	t_node	*node;

	node = command->redir_list->head;
	while (node)
	{
		handle_redir(shell, command, node->data);
		node = node->next;
	}
}
