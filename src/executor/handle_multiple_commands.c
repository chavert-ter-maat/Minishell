#include "../../include/minishell.h"

static int handle_fds(int *pipe_fd, int former_read_end)
{
    if (close(pipe_fd[WRITE_END]) == FAILED)
        perror_exit("4: close");
		
    if (former_read_end != STDIN_FILENO) // Only close if it's not STDIN_FILENO
    {
        if (close(former_read_end) == FAILED)
            perror_exit("3: close");
    }
	former_read_end = pipe_fd[READ_END];
    return (former_read_end);
}
static int	execute_last_command(t_shell *shell, int former_read_end, char *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAILED)
		perror_exit("fork");
	if (pid == SUCCES)
	{
		if (dup2(former_read_end, STDIN_FILENO) == FAILED)
			perror_exit("3: dup2");
		run_command(shell, cmd); 
	}	
	if (close(former_read_end) == FAILED)
		perror_exit("2: close");
	return(pid);
}

static void execute_children(t_shell *shell, int former_read_end, int *pipe_fd, char *cmd)
{
	if (dup2(former_read_end, STDIN_FILENO) == FAILED)
		perror_exit("2: dup2");
	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == FAILED)
		perror_exit("1: dup2");
	run_command(shell, cmd);
	if (close(pipe_fd[WRITE_END]) == FAILED)
		perror_exit("1: close");
}

static int	initiate_forks(t_shell *shell, int nb_commands, char **argv)
{
	int 	pipe_fd[2];
	pid_t	pid;
	int		former_read_end;
	int		index_command = 2;
	
	while(nb_commands != 0) // nb_commands  = 3
	{
	if (pipe(pipe_fd) == FAILED)
		perror_exit("pipe");
	pid = fork();
	if (pid == FAILED)
		perror_exit("fork");
	if (pid == SUCCES)
		execute_children(shell, former_read_end, pipe_fd, argv[index_command]);
	former_read_end = handle_fds(pipe_fd, former_read_end);
		nb_commands--;
		index_command++;
	}
	pid = execute_last_command(shell, former_read_end, argv[index_command]);
	return(pid);
}

void	handle_multiple_commands(t_shell *shell, int nb_commands, char **argv)
{
	pid_t	pid;
	
	pid = initiate_forks(shell, nb_commands, argv);
	if (waitpid(pid, NULL, 0) == FAILED)
		perror_exit("waitpid");
}
