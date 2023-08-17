/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_executor.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:01:28 by fhuisman      #+#    #+#                 */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2023/08/17 10:59:03 by cter-maa      ########   odam.nl         */
=======
/*   Updated: 2023/08/17 11:01:04 by fhuisman      ########   odam.nl         */
>>>>>>> 30decf9028202802b1a12f7473b2d341dd07cf73
=======
/*   Updated: 2023/08/17 14:05:35 by cter-maa      ########   odam.nl         */
>>>>>>> ea922aaff1dd99a4478a92a7872a8d18416ec075
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

void	change_fd_to_in(int fd)
{
	if (dup2(fd, STDIN_FILENO) == FAILED)
		perror_exit_fork(shell, "dup2")
	if (close (fd) == FAILED)
		perror_exit_fork(shell, "close")
}

void	change_fd_to_out(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == FAILED)
		perror_exit_fork(shell, "dup2")
	if (close(fd) == FAILED)
		perror_exit_fork(shell, "close")
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