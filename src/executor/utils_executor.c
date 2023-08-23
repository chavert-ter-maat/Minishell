/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_executor.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/23 16:37:50 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/08/23 17:19:07 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	wait_function(t_shell *shell, int count_childs, pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == FAILED)
		perror_exit_fork(shell, "waitpid");
	while (count_childs > 0)
	{
		wait(NULL);
		count_childs--;
	}
	if (WIFSIGNALED(status))
		shell->status = g_status;
	else
		shell->status = WEXITSTATUS(status);
}

void	change_fd_to_in(t_shell *shell, int fd)
{
	if (dup2(fd, STDIN_FILENO) == FAILED)
		perror_exit_fork(shell, "dup2");
	if (close (fd) == FAILED)
		perror_exit_fork(shell, "close");
}

void	change_fd_to_out(t_shell *shell, int fd)
{
	if (dup2(fd, STDOUT_FILENO) == FAILED)
		perror_exit_fork(shell, "dup2");
	if (close(fd) == FAILED)
		perror_exit_fork(shell, "close");
}
