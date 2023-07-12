#include "../../include/minishell.h"

void	create_single_child(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == FAILED)
		perror_exit("fork");
	// save_std(shell->executor);
	if (pid == SUCCESS)
		run_command(shell, shell->argv[2]);
	// restore_std(shell->executor);
	if (waitpid(pid, &status, 0) == FAILED)
		perror_exit("waitpid");
	// print_status_waidpid(pid, status);
}