#include "../include/minishell.h"
#include <signal.h>

// void	print_token_list(t_shell *shell) //for testing purpose
// {
// 	t_node	*temp;
// 	t_token	*token;

// 	if (!shell->token_list || !shell->token_list->head)
// 		return;
// 	temp = shell->token_list->head;
// 	while (temp)
// 	{
// 		token = (t_token *)temp->data;
// 		printf("%s\n", token->str);
// 		temp = temp->next;
// 	}
	
// }

void	f(void)
{
	system("leaks minishell");
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
	ft_signals();
	ft_bzero(&shell, sizeof(t_shell));
	init_env(&shell, envp);

	while (1)
	{
		shell.cmd_line = readline("shellyeah$ ");
		add_history(shell.cmd_line);
		lexer(&shell);
		expander(&shell);
		parser(&shell);
		// executor(&shell);
		print_command_table(&shell);
		free_shell(&shell);
	}
	return (0);
}
