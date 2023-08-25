/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_multiple_commands.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/23 16:37:28 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/08/25 12:02:43 by chavertterm   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_fds(t_shell *shell, int *pipe_fd, int read_end)
{
	if (close(pipe_fd[WRITE_END]) == FAILED)
	{
		perror_update_status(shell, "close");
		return (-1);
	}
	if (read_end != STDIN_FILENO)
	{
		if (close(read_end) == FAILED)
		{
			perror_update_status(shell, "close");
			return (-1);
		}
	}
	read_end = pipe_fd[READ_END];
	return (read_end);
}

static int	execute_last_command(t_shell *shell, t_command *command,
		int read_end)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAILED)
	{
		perror_update_status(shell, "fork");
		return (pid);
	}
	if (pid == SUCCESS)
	{
		if (dup2(read_end, STDIN_FILENO) == FAILED)
			perror_exit_fork(shell, "dup2");
		handle_redirection(shell, command, pid);
		if (check_if_builtin(command->args[0]))
		{
			execute_builtin(shell, command);
			_exit(0);
		}
		else
			execute_non_builtin(shell, command);
	}
	if (close(read_end) == FAILED)
		perror_update_status(shell, "close");
	return (pid);
}

static void	execute_childs(t_shell *shell, t_command *command,
		int read_end, int *pipe_fd)
{
	if (close(pipe_fd[READ_END]) == FAILED)
		perror_exit_fork(shell, "close");
	if (dup2(read_end, STDIN_FILENO) == FAILED)
		perror_exit_fork(shell, "dup2");
	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == FAILED)
		perror_exit_fork(shell, "dup2");
	handle_redirection(shell, command, 0);
	if (check_if_builtin(command->args[0]) == TRUE)
	{
		execute_builtin(shell, command);
		_exit(0);
	}
	else
		execute_non_builtin(shell, command);
	// if (close(pipe_fd[WRITE_END]) == FAILED) //checken op leaky pipes
	// 	perror_exit_fork(shell, "close");
}

static int	create_forks(t_shell *shell, t_command *command, int read_end,
		int *fd)
{
	pid_t	pid;

	if (pipe(fd) == FAILED)
		return (perror_update_status(shell, "pipe"), 1);
	pid = fork();
	if (pid == FAILED)
		return (perror_update_status(shell, "fork"), 1);
	if (pid == SUCCESS)
		execute_childs(shell, command, read_end, fd);
	return (0);
}

void	handle_multiple_commands(t_shell *shell, t_node *command_node)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		read_end;
	int		count_childs;

	read_end = 0;
	count_childs = 0;
	while (command_node->next)
	{
		count_childs++;
		if (create_forks(shell, command_node->data, read_end, pipe_fd))
			return ;
		read_end = handle_fds(shell, pipe_fd, read_end);
		if (read_end == -1)
			return ;
		command_node = command_node->next;
	}
	pid = execute_last_command(shell, command_node->data, read_end);
	if (pid != FAILED)
		wait_function(shell, count_childs, pid);
}
