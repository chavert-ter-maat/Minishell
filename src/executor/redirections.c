/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:04:12 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/23 13:11:31 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	redir_heredoc(t_shell *shell, t_command *command, t_redir *redir)
{
	char buff[5];
	read(redir->heredoc_read_end, buff, 5);
	printf("%s = read_end\n", buff);
	if (command->arg_list->count > 0)
		change_fd_to_in(shell, redir->heredoc_read_end);
}

static void	redir_in(t_shell *shell, char *file, t_command *command, pid_t pid)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == FAILED)
	{
		if (pid == 0)
			perror_exit_fork(shell, "open");
		else
			return (perror_update_status(shell, "open"));
	}
	if (command->arg_list->count > 0)
		change_fd_to_in(shell, fd);
}

// redirects stfout to file
static void	redir_out(t_shell *shell, char *file, t_command *command, pid_t pid)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == FAILED)
	{
		if (pid == 0)
			perror_exit_fork(shell, "open");
		else
			return (perror_update_status(shell, "open"));
	}
	if (command->arg_list->count > 0)
		change_fd_to_out(shell, fd);
}

static void	redir_append(t_shell *shell, char *file, t_command *command, pid_t pid)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == FAILED)
	{
		if (pid == 0)
			perror_exit_fork(shell, "open");
		else
			return (perror_update_status(shell, "open"));
	}
	if (command->arg_list->count > 0)
		change_fd_to_out(shell, fd);
}

static void	handle_redir(t_shell *shell, t_command *command,
		t_redir *redir, pid_t pid)
{
	if (redir->type == IN)
		return (redir_in(shell, redir->file, command, pid));
	if (redir->type == OUT)
		return (redir_out(shell, redir->file, command, pid));
	if (redir->type == HEREDOC)
		return (redir_heredoc(shell, command, redir));
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
