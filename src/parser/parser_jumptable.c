#include "../../include/minishell.h"

t_token	*add_cmd_skip(t_shell *shell, t_token *current, t_command *new)
{
	(void) shell;
	if (!new)
		return (NULL);
	else
		return ((current)->next);
}

t_redir_type	get_redir_type(char *str)
{
	if (str[0] == '>')
	{
		if (str[1] == '>')
			return (APPEND);
		if (str[1] == '\0')
			return (OUT);
	}
	if (str[0] == '<')
	{
		if (str[1] == '<')
			return (HEREDOC);
		if (str[1] == '\0')
			return (IN);
	}
	shell_error(parse_error, (const char *)str);
	return (REDIR);
}

t_token *add_cmd_redir(t_shell *shell, t_token *current, t_command *new_cmd)
{
	t_redir	*new_redir;

	if (!new_cmd)
		return (NULL);
	new_redir = ft_calloc(1, sizeof(t_redir));
	if (!new_redir)
		return (shell_error(malloc_error, "add_cmd_redir() @ ft_calloc"), free_shell(shell), NULL);
	list_add_redir(&(new_cmd->redir), new_redir);
	new_redir->type = get_redir_type(current->str);
	current = current->next;
	skip_space(&current);
	if (!current || current->type != WORD)
		return (shell_error(parse_error, "redirection"), free_shell(shell), NULL);
	new_redir->file = ft_strdup(current->str);
	if (!(new_redir->file))
		return (shell_error(malloc_error, "add_cmd_redir() @ ft_strdup"), free_shell(shell), NULL);
	return (current->next);
}

t_token	*add_cmd_word(t_shell *shell, t_token *current, t_command *new)
{
	t_argument *new_arg;

	if (!new)
		return (NULL);
	if (!new->command)
	{
		new->command = ft_strdup((const char *)current->str);
		if (!new->command)
			return (shell_error(malloc_error, "add_cmd_word() @ ft_strdup"), free_shell(shell), NULL);
	}
	else
	{
		new_arg = ft_calloc(1, sizeof(t_argument));
		if (!new_arg)
			return (shell_error(malloc_error, "add_cmd_word() @ ft_calloc"), free_shell(shell), NULL);
		list_add_arg(&(new->args), new_arg);
		new_arg->str = ft_strdup ((const char *) current->str);
		if (!(new_arg->str))
			return (shell_error(malloc_error, "add_cmd_word() @ ft_strdup"), free_shell(shell), NULL);
	}
	return (current->next);
}

