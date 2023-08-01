#include "../../include/minishell.h"

t_node	*skip_token(t_shell *shell, t_node *node, t_command *new)
{
	(void) shell;
	if (!new)
		return (NULL);
	else
		return (node->next);
}

static t_redir_type	get_redir_type(t_shell *shell, t_node *node)
{
	t_token *token;

	token = (t_token *) node->data;
	if (token->str[0] == '>')
	{
		if (token->str[1] == '>')
			return (APPEND);
		if (token->str[1] == '\0')
			return (OUT);
	}
	if (token->str[0] == '<')
	{
		if (token->str[1] == '<')
			return (HEREDOC);
		if (token->str[1] == '\0')
			return (IN);
	}
	shell_error(shell, syntax_error, (const char *)token->str, 1);
	return (REDIR);
}

t_node *add_cmd_redir(t_shell *shell, t_node *node, t_command *new_cmd)
{
	t_redir	new_redir;
	t_token *token;
	
	new_redir.type = get_redir_type(shell, node);
	node = node->next;
	skip_space(&node);
	if (!node)
		return (shell_error(shell, syntax_error, "newline", 1), NULL);
	token = (t_token *) node->data;
	if (token->type != WORD)
		return (shell_error(shell, syntax_error, token->str, 1), NULL);
	new_redir.file = ft_strdup(token->str);
	if (!(new_redir.file))
		return (shell_error(shell, malloc_error, "add_cmd_redir() @ ft_strdup", 1), NULL);
	list_add_new_node(shell, new_cmd->redir_list, &new_redir);
	return (node->next);
}

t_node	*add_cmd_arg(t_shell *shell, t_node *node, t_command *new)
{
	char	*arg;
	t_token	*token;

	token = (t_token *)node->data;
	arg = ft_strdup(token->str);
	if (!arg)
		return (shell_error(shell, malloc_error, "add_cmd_arg() @ ft_strdup", 1), NULL);
	list_add_new_node(shell, new->arg_list, &arg);
	return (node->next);
}
