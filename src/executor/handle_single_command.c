/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_single_command.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:07:07 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/22 13:29:34 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	restore_fds(int tmp_std_in, int tmp_std_out)
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
	handle_redirection(shell, command, 1);
	if (command->arg_list->count == 0)
		shell->status = 0;
	else if (check_if_builtin(command->args[0]))
		execute_builtin(shell, command);
	else
	{
		pid = fork();
		if (pid == FAILED)
			perror_exit_fork(shell, "fork"); // if fork failed use return instead of _exit?
		if (pid == SUCCESS)
			execute_non_builtin(shell, shell->command_list->head->data);
		if (waitpid(pid, &status, 0) == FAILED)
			perror_exit_fork(shell, "waitpid");
		if(WIFSIGNALED(status))
			shell->status = g_status;
		else
			shell->status = WEXITSTATUS(status);
	}
	restore_fds(tmp_std_in, tmp_std_out);
}
