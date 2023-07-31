#include "../../include/minishell.h"

// former read end becomes read end.
static int handle_fds(t_shell *shell, int *pipe_fd, int read_end)
{
    if (close(pipe_fd[WRITE_END]) == FAILED)
        perror_exit(shell, "close");
		
    if (read_end != STDIN_FILENO)
    {
        if (close(read_end) == FAILED)
            perror_exit(shell, "close");
    }
	read_end = pipe_fd[READ_END];
    return (read_end);
}
// last command is executed and the output of the command is written to the
// standart output.
static int	execute_last_command(t_shell *shell, t_command *command, int read_end)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAILED)
		perror_exit(shell, "fork");
	if (pid == SUCCESS)
	{
		if (dup2(read_end, STDIN_FILENO) == FAILED)
			perror_exit(shell, "dup2");
		execute_non_builtin(shell, command);
	}	
	if (close(read_end) == FAILED)
		perror_exit(shell, "close");
	return(pid);
}

// runs the command, the output of the command is written to the write end
// of the pipe.
void	execute_childs(t_shell *shell, t_command *command, int read_end, int *pipe_fd)
{
	if (dup2(read_end, STDIN_FILENO) == FAILED)
		perror_exit(shell, "dup2");
	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == FAILED)
		perror_exit(shell, "dup2");
    // if (check_if_builtin(command->args[0]) == TRUE)
	// 	execute_builtin(shell, command);
    // else
    	execute_non_builtin(shell, command);
	if (close(pipe_fd[WRITE_END]) == FAILED)
		perror_exit(shell, "close");
}

// creates forks for the amount of commands and pipes the output of a
// command to the input of the next command.
static int	initiate_forks(t_shell *shell, t_list *command_list) 
{
	int 	pipe_fd[2];
	pid_t	pid;
	int		read_end;
    t_node  *current;
	
    current = command_list->head;
	while(current->next) 
	{
		if (pipe(pipe_fd) == FAILED)
			perror_exit(shell, "pipe");
		pid = fork();
		if (pid == FAILED)
			perror_exit(shell, "fork");
		if (pid == SUCCESS)
			execute_childs(shell, current->data, read_end, pipe_fd);
		read_end = handle_fds(shell, pipe_fd, read_end);
		current = current->next;
	}
	pid = execute_last_command(shell, current->data, read_end);
	return(pid);
}

void	handle_multiple_commands(t_shell *shell)
{
	pid_t	pid;
	
	pid = initiate_forks(shell, shell->command_list);
	if (waitpid(pid, NULL, 0) == FAILED)
		perror_exit(shell, "waitpid");
}
