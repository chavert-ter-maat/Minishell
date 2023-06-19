#include "../../include/minishell.h"


void infile_as_stdin(t_shell *shell)
{
	int	infile_fd;

	infile_fd = open(shell->infile, O_RDONLY);
	if (infile_fd == FAILED)
		perror_exit(shell->infile);
	if (dup2(infile_fd, STDIN_FILENO) == FAILED)
		perror_exit("dup2");
	if (close(infile_fd) == FAILED)
		perror_exit("close");
}

void	outfile_as_stdout(t_shell *shell)
{
	int	fd_outfile;

	fd_outfile = open(shell->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_outfile == FAILED)
		perror_exit(shell->outfile);
	if (dup2(fd_outfile, STDOUT_FILENO) == FAILED)
		perror_exit("dup2");
	if (close(fd_outfile) == FAILED)
		perror_exit("close");
}

void	print_status_waidpid(pid_t pid, int options) 
{
	int status;
	int exit_status;
	int	signal_number;


	if (waitpid(pid, &status, options) == -1) 
		perror("waitpid");
	else 
	{
		if (WIFEXITED(status)) 
		{
			exit_status = WEXITSTATUS(status);
			printf("\nChild process with PID %d exited normally with status: %d\n"
				, pid, exit_status);
		} 
		else if (WIFSIGNALED(status)) 
		{
			signal_number = WTERMSIG(status);
			printf("\nChild process with PID %d exited due to signal:%d\n"
				, pid, signal_number);
		}
	}
}