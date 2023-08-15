#include "../../include/minishell.h"

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