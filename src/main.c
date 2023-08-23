#include "../include/minishell.h"
#include <signal.h>

static void	print_redir(t_list *redir_list) //for testing purpose
{
	t_node	*current;
	t_redir	*redir;

	printf("redir: ");
	current = redir_list->head;
	while (current)
	{
		redir = (t_redir *) current->data;
		if (redir->type == IN)
			printf("<: %s", redir->file);
		else if (redir->type == OUT)
			printf(">: %s", redir->file);
		else if (redir->type == APPEND)
			printf(">>: %s", redir->file);
		else if (redir->type == HEREDOC)
			printf("<<: %s", redir->file);
		if (current->next)
			printf(", ");
		current = current->next;
	}
	printf("\n");
}

static void	print_args(char *args[]) //for testing purpose
{
	int	i;

	printf("args:");
	i = 0;
	while (args[i])
	{
		if (i != 0)
			printf(",");
		printf(" %s", args[i]);
		i ++;
	}
	printf("\n");
}

void	print_command_table(t_shell *shell) //for testing purpose
{
	t_node		*current;
	t_command	*command;

	if (!shell->command_list)
		return ;
	current = shell->command_list->head;
	while (current)
	{
		command = (t_command *) current->data;
		printf("-----------------------command count: %d\n", shell->command_list->count);
		print_args(command->args);
		print_redir(command->redir_list);
		current = current->next;
	}
}

void	print_token_list(t_shell *shell) //for testing purpose
{
	t_node	*temp;
	t_token	*token;

	if (!shell->token_list || !shell->token_list->head)
		return ;
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
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argv;
	if (argc > 1)
		exit(1);
	atexit(f); //remove later
	init_shell(&shell, envp);
	while (1)
	{
		init_signals(PROMPT);
		shell.cmd_line = readline("shellyeah$ ");
		if (shell.cmd_line == NULL)
			eof_handler(&shell);
		add_history(shell.cmd_line);
		parser(&shell);
		executor(&shell);
		free_shell(&shell);
	}
	return (0);
}
