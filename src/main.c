#include "../include/minishell.h"
#include <signal.h>

// for testing puropses
void	exit_lexer(t_shell *shell)
{
	free_tok_list(&(shell->lexer));
	print_list(shell->expander);
	free_tok_list(&(shell->expander));
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

// executor tester
int main(int argc, char **argv, char **envp)
{
	t_shell shell;

	(void) argv;
	(void) envp;
	if (argc > 1)
		;//exit
	atexit(f);
	signal(SIGINT, &inthandler);
	ft_bzero(&shell, sizeof(t_shell));
	init_env(&shell, envp);
	while (1)
	{
		make_var_list(&shell); //for testing purpose
		shell.cmd_line = readline("shellyeah$ ");
		add_history(shell.cmd_line);
		lexer(&shell);
		expander(&shell);
		parser(&shell);
		executor(&shell);
		free_shell(&shell);
		free(shell.cmd_line);
		free(shell.var_list); //remove later
	}
}
