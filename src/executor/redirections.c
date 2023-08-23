/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:04:12 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/23 18:13:28 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redir_heredoc(t_shell *shell, t_command *command,
		t_redir *redir, pid_t pid)
{
	if (command->arg_list->count > 0)
		change_fd_to_in(shell, redir->heredoc_read_end, pid);
}

void	redir_in(t_shell *shell, char *file, t_command *command, pid_t pid)
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
		change_fd_to_in(shell, fd, pid);
}

void	redir_out(t_shell *shell, char *file, t_command *command, pid_t pid)
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
		change_fd_to_out(shell, fd, pid);
}

void	redir_append(t_shell *shell, char *file, 
			t_command *command, pid_t pid)
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
		change_fd_to_out(shell, fd, pid);
}
