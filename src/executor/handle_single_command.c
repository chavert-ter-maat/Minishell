#include "../../include/minishell.h"

void	handle_single_command(t_shell *shell, t_command *command)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == FAILED)
		perror_exit("fork");
	// save_std(shell->executor);
	if (pid == SUCCESS)
		run_arguments(shell, shell->command->args);
	// restore_std(shell->executor);
	if (waitpid(pid, &status, 0) == FAILED)
		perror_exit("waitpid");
	// print_status_waidpid(pid, status);
}