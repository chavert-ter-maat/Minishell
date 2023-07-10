#include "../../include/minishell.h"

// former read end becomes read end.
static int handle_fds(int *pipe_fd, int read_end)
{
    if (close(pipe_fd[WRITE_END]) == FAILED)
        perror_exit("4: close");
		
    if (read_end != STDIN_FILENO)
    {
        if (close(read_end) == FAILED)
            perror_exit("3: close");
    }
	read_end = pipe_fd[READ_END];
    return (read_end);
}
// last command is executed and the output of the command is written to the
// standart output.
static int	execute_last_command(t_shell *shell, int read_end, char *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAILED)
		perror_exit("fork");
	if (pid == SUCCES)
	{
		if (dup2(read_end, STDIN_FILENO) == FAILED)
			perror_exit("3: dup2");
		run_command(shell, cmd); 
	}	
	if (close(read_end) == FAILED)
		perror_exit("2: close");
	return(pid);
}

// runs the command, the output of the command is written to the write end
// of the pipe.
void	execute_childs(t_shell *shell, int read_end, int *pipe_fd, char *cmd)
{
	if (dup2(read_end, STDIN_FILENO) == FAILED)
		perror_exit("2: dup2");
	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == FAILED)
		perror_exit("1: dup2");
	run_command(shell, cmd);
	if (close(pipe_fd[WRITE_END]) == FAILED)
		perror_exit("1: close");
}

// creates forks for the amount of commands and pipes the output of 1
// command to the input of the next command.
static int	initiate_forks(t_shell *shell, int nb_commands, char **argv)
{
	int 	pipe_fd[2];
	pid_t	pid;
	int		read_end;
	int		index_command = 2;
	
	while(nb_commands != 0) 
	{
	if (pipe(pipe_fd) == FAILED)
		perror_exit("pipe");
	pid = fork();
	if (pid == FAILED)
		perror_exit("fork");
	if (pid == SUCCES)
		execute_childs(shell, read_end, pipe_fd, argv[index_command]);
	read_end = handle_fds(pipe_fd, read_end);
		nb_commands--;
		index_command++;
	}
	pid = execute_last_command(shell, read_end, argv[index_command]);
	return(pid);
}

void	handle_multiple_commands(t_shell *shell, int nb_commands, char **argv)
{
	pid_t	pid;
	
	pid = initiate_forks(shell, nb_commands, argv);
	if (waitpid(pid, NULL, 0) == FAILED)
		perror_exit("waitpid");
}
