#include "../../include/minishell.h"

void	restore_std(int tmp_std_in, int tmp_std_out)
{
	dup2(tmp_std_in, STDIN_FILENO);
	dup2(tmp_std_out, STDOUT_FILENO);
	close(tmp_std_in);
	close(tmp_std_out);
}

//execute command without pipe
void	handle_single_command(t_shell *shell, t_command *command)
{
	pid_t	pid;
	int		status;
	int		tmp_std_in;
	int		tmp_std_out;

	tmp_std_in = dup(STDIN_FILENO);
	tmp_std_out = dup(STDOUT_FILENO);
	handle_redirection(shell, command, "YES_COMMAND");
	if (check_if_builtin(command->args[0]))
		return (execute_builtin(shell, command));
	else
	{
		pid = fork();
		if (pid == FAILED)
			error_exit_fork(shell, "fork");
		if (pid == SUCCESS)
			execute_non_builtin(shell, shell->command_list->head->data);
		if (waitpid(pid, &status, 0) == FAILED)
				error_exit_fork(shell, "waitpid");
		if (WIFEXITED(status))
		 	g_status = WEXITSTATUS(status);
	}
	restore_std(tmp_std_in, tmp_std_out);
}
