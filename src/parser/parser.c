#include "../../include/minishell.h"

typedef t_token	*(*t_add_cmd_func)(t_shell *, t_token *, t_command *);

void	print_redir(t_redir *top) //for testing purpose
{
	t_redir	*temp;

	printf("redir: ");
	temp = top;
	while (temp)
	{
		if (temp->type == IN)
			printf("<: %s, ", temp->file);
		if (temp->type == OUT)
			printf(">: %s, ", temp->file);
		if (temp->type == APPEND)
			printf(">>: %s, ", temp->file);
		if (temp->type == HEREDOC)
			printf("<<: %s, ", temp->file);
		temp = temp->next;
	}
	printf("\n");
}

void	print_args(t_argument *top) //for testing purpose
{
	t_argument	*temp;

	printf("args: ");
	temp = top;
	while (temp)
	{
		printf("%s, ", temp->str);
		temp = temp->next;
	}
	printf("\n");
}

void	print_command_table(t_shell *shell) //for testing purpose
{
	t_command *temp;

	temp = shell->parser;
	while (temp)
	{
		printf("------------------------------\n");
		printf("command name: %s\n", temp->command);
		print_args(temp->args);
		print_redir(temp->redir);
		temp = temp->next;
	}
}

t_token	*fill_command(t_shell *shell, t_token *current, t_command *new)
{
	const t_add_cmd_func	func[8] = {
	[0] = &add_cmd_skip,
	[1] = NULL,
	[2] = NULL,
	[3] = &add_cmd_redir,
	[4] = &add_cmd_redir,
	[5] = NULL,
	[6] = &add_cmd_skip,
	[7] = &add_cmd_word,
	};
	if (!new)
		return (NULL);
	if (current && current->type == PIPE)
		return (shell_error(syntax_error, current->str), free_shell(shell), NULL);
	while (current && current->type != PIPE)
		current = func[current->type](shell, current new);
	// if (valid_command(new) == false)
			//return (NULL);
	if (current)
		current = func[current->type](shell, current, new);
	return (current);
}

void	add_cmd(t_shell *shell, t_token **current)
{
	t_command	*new;
	t_argument	*args;
	
	skip_space(current);
	new = list_add_new_cmd(shell);
	*current = fill_command(shell, *current, new);
	new->args = arg_list_to_array(new);
}

void	parser(t_shell *shell)
{
	t_token		*current;

	current = shell->expander;
	while (current)
		add_cmd(shell, &current);
}