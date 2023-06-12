#include "../include/minishell.h"

// int	main(int argc, char *argv[], char *envp[])
// {
// 	t_shell	shell;

// 	(void) argv;
// 	(void) envp;
// 	if (argc > 1)
// 		;//exit
// 	while (1)
// 	{
// 		shell.cmd_line = readline("shellyeah$ ");
// 		add_history(shell.cmd_line);
// 		shell.tokens = lexer(&shell);
// 		free(shell.cmd_line);
// 	}
// }

// executor tester
int main(int argc, char **argv, char **envp)
{
	t_shell shell;

	if(argc != 4)
	{
		ft_putstr_fd("wrong argyment input", 1);
		exit(EXIT_FAILURE);
	}
	input_handling(&shell, argc, argv, envp);
	infile_as_stdin(&shell);
	outfile_as_stdout(&shell);
	create_single_child(&shell);

	// if(argc > 3)
	// 	handle_multiple_commands(&shell);
	return(0);
}