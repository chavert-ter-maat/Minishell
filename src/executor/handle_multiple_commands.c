/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_multiple_commands.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/23 16:37:28 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/08/23 16:44:49 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_fds(t_shell *shell, int *pipe_fd, int read_end)
{
	if (close(pipe_fd[WRITE_END]) == FAILED)
		perror_exit_fork(shell, "close");
	if (read_end != STDIN_FILENO)
	{
		if (close(read_end) == FAILED)
			perror_exit_fork(shell, "close");
	}
	read_end = pipe_fd[READ_END];
	return (read_end);
}

int	execute_last_command(t_shell *shell, t_command *command, int read_end)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAILED)
		perror_exit_fork(shell, "fork");
	if (pid == SUCCESS)
	{
		if (dup2(read_end, STDIN_FILENO) == FAILED)
			perror_exit_fork(shell, "dup2");
		handle_redirection(shell, command, pid);
		if (check_if_builtin(command->args[0]))
			execute_builtin(shell, command);
		else
			execute_non_builtin(shell, command);
	}
	if (close(read_end) == FAILED)
		perror_exit_fork(shell, "close");
	return (pid);
}

void	execute_childs(t_shell *shell, t_command *command, 
		int read_end, int *pipe_fd)
{
	if (dup2(read_end, STDIN_FILENO) == FAILED)
		perror_exit_fork(shell, "dup2");
	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == FAILED)
		perror_exit_fork(shell, "dup2");
	handle_redirection(shell, command, 0);
	if (check_if_builtin(command->args[0]) == TRUE)
		execute_builtin(shell, command);
	else
		execute_non_builtin(shell, command);
	if (close(pipe_fd[WRITE_END]) == FAILED)
		perror_exit_fork(shell, "close");
}

void	create_forks(t_shell *shell, t_command *command, int read_end, int *fd)
{
	pid_t	pid;

	if (pipe(fd) == FAILED)
		perror_exit_fork(shell, "pipe");
	pid = fork();
	if (pid == FAILED)
		perror_exit_fork(shell, "fork");
	if (pid == SUCCESS)
		execute_childs(shell, command, read_end, fd);
}

void	handle_multiple_commands(t_shell *shell)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		read_end;
	t_node	*current;
	int		count_childs;

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
