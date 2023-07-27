#include "../../include/minishell.h"

void	handle_single_command(t_shell *shell, t_command *command)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == FAILED)
		perror_exit(shell, "fork");
	// save_std(shell->executor);
	if (pid == SUCCESS)
    {
        if (check_if_builtin(command->args[0]))
            execute_builtin(shell, command);
        else 
		    execute_non_builtin(shell, shell->command_list->head->data);

    }
	// restore_std(shell->executor);
	if (waitpid(pid, &status, 0) == FAILED)
		perror_exit(shell, "waitpid");
	// print_status_waidpid(pid, status);
}