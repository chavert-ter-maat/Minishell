#include "../../include/minishell.h"

void	input_error(void)
{
	ft_putstr_fd("wrong input: infile cmd1 cmd2 outfile\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	error_exit(char *input)
{
	ft_putstr_fd(input, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

//set errno?
void	perror_exit(char *input)
	{
		ft_putstr_fd("Shell_yeah: ", STDERR_FILENO);
		perror(input);
		exit(EXIT_FAILURE);
	}

void	error_no_command(char *cmd)
{
	ft_putstr_fd("Shell_yeah: ", STDERR_FILENO);
	if(cmd != NULL)
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("command not found\n", STDERR_FILENO);
	exit(127);
}
