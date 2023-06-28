#include "../include/minishell.h"
#include <signal.h>

// for testing puropses

void	exit_parser(t_shell *shell)
{
	print_command_table(shell);
	free_shell(shell);
}

void	inthandler(int signum) // for testing purpose
{
	if (signum == SIGINT)
		exit(EXIT_SUCCESS);
}
void	f(void)
{
	system("leaks minishell");
}

void	make_var_list(t_shell *shell) //for testing purpose
{
	t_var *new;

	new = ft_calloc(1, sizeof(t_var));
	new->name = "VAR";
	new->value = "value";
	shell->var_list = new;
}

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

	(void) argv;
	(void) envp;
	if (argc > 1)
		exit(EXIT_FAILURE);
	atexit(f);
	signal(SIGINT, &inthandler);
	ft_bzero(&shell, sizeof(t_shell));
	while (1)
	{
		make_var_list(&shell); //for testing purpose
		shell.cmd_line = readline("shellyeah$ ");
		add_history(shell.cmd_line);
		lexer(&shell);
		expander(&shell);
		parser(&shell);
		exit_parser(&shell);//remove later
		if (shell.cmd_line)
			free(shell.cmd_line);
		free_var_list(&(shell.var_list)); //remove later
	}
    
// main for executor

// int main(int argc, char **argv, char **envp)
// {
// 	t_shell shell;

// 	if(argc != 4) //1 cmd
// 	{
// 		ft_putstr_fd("wrong argument input", 1);
// 		exit(EXIT_FAILURE);
// 	}
// 	input_handling(&shell, argc, argv, envp);
// 	infile_as_stdin(&shell);
// 	outfile_as_stdout(&shell);
// 	create_single_child(&shell);
// 	// argc -= 4;
// 	// handle_multiple_commands(&shell, argc, argv); 
// 	return(0);
// }
}