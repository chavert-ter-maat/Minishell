/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_single_command.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:07:07 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/24 13:45:36 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	wait_function_single_command(t_shell *shell, int status, int pid)
{
	if (waitpid(pid, &status, 0) == FAILED)
		perror_exit_fork(shell, "waitpid");
	if (WIFSIGNALED(status))
		shell->status = g_status;
	else
		shell->status = WEXITSTATUS(status);
}

static void	restore_fds(t_shell *shell, int tmp_std_in, int tmp_std_out)
{
	if (dup2(tmp_std_in, STDIN_FILENO) == FAILED)
		perror_update_status(shell, "dup2");
	if (dup2(tmp_std_out, STDOUT_FILENO) == FAILED)
		perror_update_status(shell, "dup2");
	if (close(tmp_std_in) == FAILED)
		perror_update_status(shell, "close");
	if (close(tmp_std_out) == FAILED)
		perror_update_status(shell, "close");
}

//execute command without pipe
void	handle_single_command(t_shell *shell, t_command *command)
{
	pid_t	pid;
	int		status;
	int		tmp_std_in;
	int		tmp_std_out;

	status = 0;
	tmp_std_in = dup(STDIN_FILENO);
	tmp_std_out = dup(STDOUT_FILENO);
	handle_redirection(shell, command, 1);
	if (command->arg_list->count == 0)
		shell->status = 0;
	else if (check_if_builtin(command->args[0]))
		execute_builtin(shell, command);
	else
	{
		pid = fork();
		if (pid == FAILED)
			return (perror_update_status(shell, "fork"));
		if (pid == SUCCESS)
			execute_non_builtin(shell, shell->command_list->head->data);
		wait_function_single_command(shell, status, pid);
	}
	restore_fds(shell, tmp_std_in, tmp_std_out);
}
