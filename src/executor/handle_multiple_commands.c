/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_multiple_commands.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:07:38 by fhuisman      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2023/08/17 10:59:08 by cter-maa      ########   odam.nl         */
=======
/*   Updated: 2023/08/17 11:15:41 by fhuisman      ########   odam.nl         */
>>>>>>> 30decf9028202802b1a12f7473b2d341dd07cf73
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// former read end becomes read end.
static int	handle_fds(t_shell *shell, int *pipe_fd, int read_end)
{
	if (close(pipe_fd[WRITE_END]) == FAILED)
		error_exit_fork(shell, "close");
	if (read_end != STDIN_FILENO)
	{
		if (close(read_end) == FAILED)
			error_exit_fork(shell, "close");
	}
	read_end = pipe_fd[READ_END];
	return (read_end);
}

// last command is executed and the output of the command is written to the
// standart output.
static int	execute_last_command(t_shell *shell,
		t_command *command, int read_end)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAILED)
		error_exit_fork(shell, "fork");
	if (pid == SUCCESS)
	{
		if (dup2(read_end, STDIN_FILENO) == FAILED)
			error_exit_fork(shell, "dup2");
		handle_redirection(shell, command, pid);
		execute_non_builtin(shell, command);
	}
	if (close(read_end) == FAILED)
		error_exit_fork(shell, "close");
	return (pid);
}

// runs the command, the output of the command is written to the write end
// of the pipe.
static void	execute_childs(t_shell *shell, t_command *command,
		int read_end, int *pipe_fd)
{
	if (dup2(read_end, STDIN_FILENO) == FAILED)
		error_exit_fork(shell, "dup2");
	if (check_redir_type(command) != HEREDOC)
	{
		if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == FAILED)
			error_exit_fork(shell, "dup2");
		handle_redirection(shell, command, 0);
	}
	else if (check_redir_type(command) == HEREDOC)
	{
		handle_redirection(shell, command, 0);
		if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == FAILED)
			error_exit_fork(shell, "dup2");
	}
	if (check_if_builtin(command->args[0]) == TRUE)
	{
		execute_builtin(shell, command);
		_exit(0);
	}
	else
		execute_non_builtin(shell, command);
	if (close(pipe_fd[WRITE_END]) == FAILED)
		error_exit_fork(shell, "close");
}

void	create_forks(t_shell *shell, t_command *command,
		int read_end, int *pipe_fd)
{
	pid_t	pid;

	if (pipe(pipe_fd) == FAILED)
		error_exit_fork(shell, "pipe");
	pid = fork();
	if (pid == FAILED)
		error_exit_fork(shell, "fork");
	if (pid == SUCCESS)
		execute_childs(shell, command, read_end, pipe_fd);
}

// creates forks for the amount of commands and pipes the output of a
// command to the input of the next command.
void	handle_multiple_commands(t_shell *shell)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		read_end;
	t_node	*current;
	int		count_childs;
	// int		status;

	read_end = 0;
	count_childs = 1;
	current = shell->command_list->head;
	while (current->next)
	{
		count_childs++;
		create_forks(shell, current->data, read_end, pipe_fd);
		read_end = handle_fds(shell, pipe_fd, read_end);
		current = current->next;
	}
	pid = execute_last_command(shell, current->data, read_end);
	wait_function(shell, count_childs, pid);
}
