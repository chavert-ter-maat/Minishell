#include "../../include/minishell.h"

void	handle_single_command(t_shell *shell, t_command *command)
{
	pid_t	pid;
	int		status;

	// save_std(shell->executor);
	if (check_if_builtin(command->args[0]))
	{
		execute_builtin(shell, command);
		return ;
	}
	else
	{
		pid = fork();
		if (pid == FAILED)
			error_exit_fork(shell, "fork");
		if (pid == SUCCESS)
			execute_non_builtin(shell, shell->command_list->head->data);
		if (waitpid(pid, &status, 0) == FAILED)
				error_exit_fork(shell, "waitpid");
		 shell->return_value = WEXITSTATUS(status);
	}
}
// 	// restore_std(shell->executor);
// 	print_status_waidpid(pid, status);
// // }