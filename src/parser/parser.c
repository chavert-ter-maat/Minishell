#include "../../include/minishell.h"

typedef t_node	*(*t_add_cmd_func)(t_shell *, t_node *, t_command *);

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

char	**arg_list_to_array(t_command *command)
{
	char	**args;
	t_node	*temp;
	int		i;

	args = ft_calloc(command->arg_list->count + 1, sizeof(char *));
	i = 0;
	if (args && command->arg_list)
	{
		temp = command->arg_list->head;
		while (temp)
		{
			if (i == 0)
				ft_strtolower((char *) temp->data);
			args[i] = (char *) temp->data;
			temp = temp->next;
			i++;
		}
	}
    return (args);
}

static t_node	*fill_command(t_shell *shell, t_node *node, t_command *new)
{
	const t_add_cmd_func	func[9] = {
	[0] = &skip_token,
	[1] = &skip_token,
	[2] = NULL,
	[3] = NULL,
	[4] = &add_cmd_redir,
	[5] = &add_cmd_redir,
	[6] = NULL,
	[7] = &skip_token,
	[8] = &add_cmd_arg,
	};
	t_token	*token;

	if (node)
		token = (t_token *) node->data;
	while (shell->token_list && node && token->type != PIPE)
	{
		node = func[token->type](shell, node, new);
		if (node)
			token = (t_token *) node->data;
	}
	if (shell->token_list && node)
		node = func[token->type](shell, node, new);
	return (node);
}

void	skip_space(t_node **node)
{
	t_token	*token;

	if (!*node)
		return ;
	token = (t_token *) (*node)->data;
	while (token && token->type == SPACE)
	{
		*node = (*node)->next;
		if (*node)
			token = (t_token *) (*node)->data;
		else
			return ;
	}
}

static void	add_cmd(t_shell *shell, t_node **node)
{
	t_token		*token;
	t_command	new;
	
	skip_space(node);
	if (!*node)
		return;
	token = (t_token *) (*node)->data;
	if (token->type == PIPE)
		return (shell_error(shell, syntax_error, token->str, 258));
	new.arg_list = list_create(shell, sizeof(char *), NULL, comp_arg);
	new.redir_list = list_create(shell, sizeof(t_redir), free_redir, comp_redir);
	*node = fill_command(shell, *node, &new);
	new.args = arg_list_to_array(&new);
	list_add_new_node(shell, shell->command_list, &new);
}

void	parser(t_shell *shell)
{
	t_node		*node;

    shell->command_list = list_create(shell, sizeof(t_command), free_command, comp_command);
	if (!shell->command_list)
		return ;
	node = shell->token_list->head;
	while (shell->command_list && node)
		add_cmd(shell, &node);
}
