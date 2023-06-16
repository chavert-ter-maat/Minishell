#include "../../include/minishell.h"

void	create_single_child(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == FAILED)
		perror_exit("fork");
	if (pid == SUCCES)
		run_command(shell, shell->argv[2]);
	if (waitpid(pid, &status, 0) == FAILED)
		perror_exit("waitpid");
	print_status_waidpid(pid, status);
}