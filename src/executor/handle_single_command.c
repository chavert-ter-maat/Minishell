#include "../../include/minishell.h"

void	handle_single_command(t_shell *shell, t_command *command)
{
	pid_t	pid;
	int		status;

	// save_std(shell->executor);
<<<<<<< HEAD
	if (pid == SUCCESS)
    {
        if (check_if_builtin(command->args[0]))
            execute_builtin(shell, command);
        else 
		{
		    execute_non_builtin(shell, shell->command_list->head->data);
			if (waitpid(pid, &status, 0) == FAILED)
				perror_exit(shell, "waitpid");
		}
    }
=======
	if (check_if_builtin(command->args[0]))
	{
		execute_builtin(shell, command);
		return ;
	}
	else
	{
		pid = fork();
		if (pid == FAILED)
			perror_exit(shell, "fork");
		if (pid == SUCCESS)
			execute_non_builtin(shell, shell->command_list->head->data);
		if (waitpid(pid, &status, 0) == FAILED)
				perror_exit(shell, "waitpid");
	}
}
>>>>>>> 498a02c66b7f75bf5846ca0f7d5e8963084c22c7
	// restore_std(shell->executor);
	// print_status_waidpid(pid, status);
// }