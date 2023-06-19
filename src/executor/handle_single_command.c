#include "../../include/minishell.h"

// static void	save_std(t_executor *executor)
// {
// 	ft_printf("hoi");
// 	executor->temp_stdin = dup(STDIN_FILENO);
// 	if(executor->temp_stdin == FAILED)
// 		{
// 			printf("failed");
// 			exit(1);
// 		}
// 	ft_printf("%i\n", executor->temp_stdin);
// 	executor->temp_stdout = dup(STDOUT_FILENO);
// 	ft_printf("%i\n", executor->temp_stdout);
// }

// static void	restore_std(t_executor *executor)
// {
// 	dup2(executor->temp_stdin, 0);
// 	dup2(executor->temp_stdout, 1);
//     close(executor->temp_stdin);
//     close(executor->temp_stdout);
// }

void	create_single_child(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == FAILED)
		perror_exit("fork");
	// save_std(shell->executor);
	if (pid == SUCCES)
		run_command(shell, shell->argv[2]);
	// restore_std(shell->executor);
	if (waitpid(pid, &status, 0) == FAILED)
		perror_exit("waitpid");
	// print_status_waidpid(pid, status);
}