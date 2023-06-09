
#include "../../include/minishell.h"
#include "../../include/execute.h"

// this function only works on 2 commands and therefor should only be used as
// an example.

static int	close_pipe_wait(t_pipex *generate)
{
	int	status;

	if (close(generate->pipe_fd[PIPE_READ_END]) == FAILED)
		perror_exit("close");
	if (close(generate->pipe_fd[PIPE_WRITE_END]) == FAILED)
		perror_exit("close");
	if (waitpid(generate->child_pid_1, NULL, 0) == FAILED)
		perror_exit("waitpid");
	if (waitpid(generate->child_pid_2, &status, 0) == FAILED)
		perror_exit("waitpid");
	return (status);
}