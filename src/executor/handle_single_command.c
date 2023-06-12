#include "../../include/minishell.h"

void	create_single_child(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == FAILED)
		perror_exit("fork");
	if (pid == SUCCES)
		run_commands(shell);
	if (waitpid(pid, &status, 0) == FAILED)
		perror_exit("waitpid");
}