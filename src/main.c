#include "../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	shell;

	(void) argv;
	(void) envp;
	if (argc > 1)
		;//exit
	while (1)
	{
		shell.cmd_line = readline("shellyeah$ ");
		add_history(shell.cmd_line);
		shell.tokens = lexer(&shell);
		free(shell.cmd_line);
	}
}
