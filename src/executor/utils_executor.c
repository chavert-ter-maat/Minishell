/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_executor.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/23 16:37:50 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/08/25 11:50:12 by chavertterm   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	wait_function(t_shell *shell, int count_childs, pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == FAILED)
		return (perror_update_status(shell, "waitpid"));
	while (count_childs >= 0)
	{
		wait(NULL);
		count_childs--;
	}
	if (WIFSIGNALED(status))
		shell->status = g_status;
	else
		shell->status = WEXITSTATUS(status);
}

int	change_fd_to_in(t_shell *shell, int fd, pid_t pid)
{
	if (dup2(fd, STDIN_FILENO) == FAILED)
	{
		if (pid == 0)
			perror_exit_fork(shell, "dup2");
		else
			return (perror_update_status(shell, "dup2"), 0);
	}
	if (close (fd) == FAILED)
	{
		if (pid == 0)
			perror_exit_fork(shell, "close");
		else
			return (perror_update_status(shell, "close"), 0);
	}
	return (1);
}

int	change_fd_to_out(t_shell *shell, int fd, pid_t pid)
{
	if (dup2(fd, STDOUT_FILENO) == FAILED)
	{
		if (pid == 0)
			perror_exit_fork(shell, "dup2");
		else
			return (perror_update_status(shell, "dup2"), 0);
	}
	if (close(fd) == FAILED)
	{
		if (pid == 0)
			perror_exit_fork(shell, "close");
		else
			return (perror_update_status(shell, "close"), 0);
	}
	return (1);
}
