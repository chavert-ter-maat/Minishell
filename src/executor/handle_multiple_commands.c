#include "../../include/minishell.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// // Function to redirect input
// void redirectInput(int* fdin, int* tmpin, const char* infile) {
//     if (infile != NULL) {
//         *fdin = open(infile, O_RDONLY);
//     } else {
//         // Use default input
//         *fdin = dup(*tmpin);
//     }
// }

// // Function to redirect output
// int redirectOutput(int i, int numsimplecommands, int* fdout, int* tmpout, const char* outfile) {
//     if (i == numsimplecommands - 1) {
//         // Last simple command
//         if (outfile != NULL) {
//             *fdout = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
//         } else {
//             // Use default output
//             *fdout = dup(*tmpout);
//         }
//     } else {
//         // Not the last simple command
//         // Create a pipe
//         int fdpipe[2];
//         pipe(fdpipe);
//         *fdout = fdpipe[1];
//         *fdin = fdpipe[0];
//     }
//     return *fdout;
// }

// // Function to execute a simple command
// void executeSimpleCommand(const char* command, char* const arguments[]) {
//     execvp(command, arguments);
//     perror("execvp");
//     _exit(1);
// }

// // Main execute function
// void execute() {
//     // Save stdin and stdout
//     int tmpin = dup(0);
//     int tmpout = dup(1);

//     int fdin;
//     int ret;
//     int fdout;

//     int i = 0;
//     while (i < numsimplecommands) {
//         // Redirect input
//         redirectInput(&fdin, &tmpin, scmd[i].infile);
//         close(fdin);

//         // Setup output
//         fdout = redirectOutput(i, numsimplecommands, &fdout, &tmpout, scmd[i].outfile);
//         close(fdout);

//         // Redirect output
//         dup2(fdout, 1);
//         close(fdout);

//         // Create child process
//         ret = fork();
//         if (ret == 0) {
//             executeSimpleCommand(scmd[i].args[0], scmd[i].args);
//         }

//         i++;
//     }

//     // Restore stdin and stdout defaults
//     dup2(tmpin, 0);
//     dup2(tmpout, 1);
//     close(tmpin);
//     close(tmpout);

//     if (!background) {
//         // Wait for the last command
//         waitpid(ret, NULL, 0);
//     }
// }

static void	save_std(t_executor *executor)
{
	executor->temp_stdin = dup(0);
	executor->temp_stdin = dup(1);
}

static void	restore_std(t_executor *executor)
{
	dup2(executor->temp_stdin, 0);
	dup2(executor->temp_stdout, 1);
    close(executor->temp_stdin);
    close(executor->temp_stdout);
}
static int	handle_fds(int *pipe_fd, int former_read_end)
{
	if(close(pipe_fd[WRITE_END]) == FAILED)
		perror_exit("close");
	former_read_end = dup(pipe_fd[READ_END]);
	if(former_read_end == FAILED)
		perror_exit("dup");
	if(close(pipe_fd[READ_END]) == FAILED)
		perror_exit("close");
	return(former_read_end);
}
static int	execute_last_command(t_shell *shell, int former_read_end, int *pipe_fd)
{
	pid_t	pid;

	if (close(pipe_fd[WRITE_END]) == FAILED)
		perror_exit("close");
	pid = fork();
	if (pid == FAILED)
		perror_exit("fork");
	if (pid == SUCCES)
	{
		if (dup2(former_read_end, STDIN_FILENO) == FAILED)
			perror_exit("dup2");
			run_command(shell); //command toevoegen
	}	
	if (close(former_read_end) == FAILED)
		perror_exit("close");
	return(pid);
}

static int execute_children(t_shell *shell, int former_read_end, int *pipe_fd)
{
	if (close(pipe_fd[READ_END]) == FAILED)
		perror_exit("close");
	if (dup2(former_read_end, STDIN_FILENO) == FAILED)
		perror_exit("dup2");
	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == FAILED)
		perror_exit("dup2");
	run_command(shell);
	if (close(pipe_fd[WRITE_END]) == FAILED)
		perror_exit("close");
	return (former_read_end);
}

static int	initiate_forks(t_shell *shell, int nb_commands)
{
	int 	pipe_fd[2];
	pid_t	pid;
	int		former_read_end;
	int		index = 0;
	
	former_read_end = STDIN_FILENO;
	while(nb_commands)
	{
	if (pipe(pipe_fd) == FAILED)
		perror_exit("pipe");
	pid = fork();
	if (pid == FAILED)
		perror_exit("fork");
	if (pid == SUCCES)
		execute_children(shell, former_read_end, pipe_fd);
	former_read_end = handle_fds(pipe_fd, former_read_end);
		nb_commands--;
	}
	pid = execute_last_command(shell, former_read_end, pipe_fd);
	return(pid);
}

void	handle_multiple_commands(t_shell *shell, int nb_commands)
{
	pid_t	pid;
	
	save_std(shell->executor);
	pid = initiate_forks(shell, nb_commands);
	restore_std(shell->executor);
	if (waitpid(pid, NULL, 0) == FAILED)
		perror_exit("waitpid");
}
