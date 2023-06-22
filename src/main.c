#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell shell;

	if(argc != 4) //1 cmd
	{
		ft_putstr_fd("wrong argument input", 1);
		exit(EXIT_FAILURE);
	}
	input_handling(&shell, argc, argv, envp);
	infile_as_stdin(&shell);
	outfile_as_stdout(&shell);
	create_single_child(&shell);
	// argc -= 4;
	// handle_multiple_commands(&shell, argc, argv); 
	return(0);
}