#include "../include/minishell.h"
#include <signal.h>

// for testing puropses
void	exit_lexer(t_shell *shell)
{
	free_list(shell->lexer);
	print_list(shell->expander);
	free_list(shell->expander);
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

	new = malloc(sizeof(t_var));
	new->name = "VAR";
	new->value = "value";
	new->next = NULL;
	shell->var_list = new;
}

// // executor tester
// int main(int argc, char **argv, char **envp)
// {
// 	t_shell shell;

// 	(void) argv;
// 	(void) envp;
// 	if (argc > 1)
// 		;//exit
// 	atexit(f);
// 	signal(SIGINT, &inthandler);
// 	ft_bzero(&shell, sizeof(t_shell));
// 	while (1)
// 	{
// 		make_var_list(&shell); //for testing purpose
// 		shell.cmd_line = readline("shellyeah$ ");
// 		add_history(shell.cmd_line);
// 		shell.lexer = lexer(&shell);
// 		shell.expander = expander(&shell);
// 		exit_lexer(&shell);//remove later
// 		shell.lexer = NULL;
// 		shell.expander = NULL;
// 		free(shell.cmd_line);
// 		free(shell.var_list); //remove later
// 	}


// // // main to test env
// int main(int argc, char **argv, char **envp)
// {
// 	t_env	*env_list;

// 	atexit()
// 	(void) argc;
// 	(void) argv;
// 	env_list = NULL;
// 	env_list = init_env(envp);
// 	print_list_env(env_list);
// 	free_list_env(env_list);
// 	return(0);
// }