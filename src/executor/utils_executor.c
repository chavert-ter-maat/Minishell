/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_executor.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:01:28 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/17 15:15:02 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	wait_function(t_shell *shell, int count_childs, pid_t pid)
{
	int status;	

	if (waitpid(pid, &status, 0) == FAILED)
		perror_exit_fork(shell, "waitpid");
	while (count_childs > 0)
	{
		wait(NULL);
		count_childs--;
	}
	if (WIFEXITED(status)) //hiervoor hebben we welwaitpid nodig
		g_status = WEXITSTATUS(status);
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
// prints the status of waidpid.
// void	print_status_waidpid(pid_t pid, int options) 
// {
// 	int status;
// 	int exit_status;
// 	int	signal_number;

// 	if (waitpid(pid, &status, options) == -1) 
// 		perror("waitpid");
// 	else 
// 	{
// 		if (WIFEXITED(status)) 
// 		{
// 			exit_status = WEXITSTATUS(status);
// 			printf("\nChild process with PID %d exited normally with status: %d\n"
// 				, pid, exit_status);
// 		} 
// 		else if (WIFSIGNALED(status)) 
// 		{
// 			signal_number = WTERMSIG(status);
// 			printf("\nChild process with PID %d exited due to signal:%d\n"
// 				, pid, signal_number);
// 		}
// 	}
// }