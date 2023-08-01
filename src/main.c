#include "../include/minishell.h"
#include <signal.h>

void	print_token_list(t_shell *shell) //for testing purpose
{
	t_node	*temp;
	t_token	*token;

	if (!shell->token_list || !shell->token_list->head)
		return;
	temp = shell->token_list->head;
	printf("Token list: (%d)\n", shell->token_list->count);
	while (temp)
	{
		token = (t_token *)temp->data;
		printf("%s\n", token->str);
		temp = temp->next;
	}
	
}

void	f(void)
{
	system("leaks minishell");
}

// executor tester
int main(int argc, char **argv, char **envp)
{
	t_shell shell;

	(void) argv;
	if (argc > 1)
		exit(1);
	atexit(f);
	ft_bzero(&shell, sizeof(t_shell));
	init_env(&shell, envp);
	while (1)
	{
		init_signals();
		shell.cmd_line = readline("shellyeah$ ");
		if (shell.cmd_line == NULL)
			sigquit_handler(&shell);
		else
		{
			add_history(shell.cmd_line);
			parser(&shell);
			executor(&shell);
		}
		free_shell(&shell);
	}
	return (0);
}
