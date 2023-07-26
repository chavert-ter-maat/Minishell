#include "../../include/minishell.h"

static void	list_add_expand_var(t_shell *shell, t_list *list, char *name)
{
	t_token new;

	new.str = expand_var(shell, name);
	new.type = WORD;
	if (!new.str)
		return ;
	list_add_new_node(shell, list, &new);
}

/* splits the string in WORDS and VAR tokens,
expands the VARs to their value and adds them
to the list */

static void	split_str_in_tokens(t_shell *shell, t_list *list, char *str)
{
	size_t	i;
	size_t	save_i;
	char	*var_name;

	i = 0;
	while(str[i])
	{
		save_i = i;
		if (str[i] != '$')
			list_add_new_word(shell, list, str, &i);
		else
		{
			save_i++;
			i = 0;
			find_end_var(&(str[save_i]), &i, VAR);
			i += save_i;
			var_name = ft_strndup(&(str[save_i]), i - save_i);
			if (!var_name)
				return (shell_error(shell, malloc_error, "split_str_in_tokens()", 1), free(str));
			list_add_expand_var(shell, list, var_name);
			free(var_name);
		}
		if (!shell->token_list)
			break ;
	}
	free(str);
}

static void	expand_quote(t_shell *shell, t_list *list, t_token *token)
{
	size_t	len;
	char	*str;
	char	quote;
	t_token	new;

	if (token->type == QUOTE)
		quote = '\'';
	else if (token->type == DQUOTE)
		quote = '\"';
	str = token->str;
	len = ft_strlen(str);
	if (len < 2 || str[0] != quote || str[len - 1] != quote)
		return (shell_error(shell, print_error, "unclosed quotes", 1));
	str = ft_strndup(str + 1, ft_strlen(str) - 2);
	if (!str)
		return (shell_error(shell, malloc_error, "expand_quote()", 1));
	if (token->type == QUOTE)
	{
		new.str = str;
		new.type = WORD;
		list_add_new_node(shell, list, &new);
	}
	else if (token->type == DQUOTE)
		split_str_in_tokens(shell, list, str);
}

static t_list	*expand_token_list(t_shell *shell, t_list *list)
{
	t_token	*token;
	t_node	*current;

	if (!list)
		return (NULL);
	current = shell->token_list->head;
	while (current)
	{
		token = (t_token *) current->data;
		if (token->type == QUOTE || token->type == DQUOTE)
			expand_quote(shell, list, token);
		else if (token->type == VAR)
			list_add_expand_var(shell, list, token->str + 1);
		else
			list_add_token_copy(shell, list, token);
		if (shell->token_list == NULL)
			return(free_list(list));
		current = current->next;
	}
	return (list);
}

void	expander(t_shell *shell)
{
	t_list	*list;

	list = list_create(shell, sizeof(t_token), free_token, comp_token);
	list = expand_token_list(shell, list);
	list_cat_words(shell, list);
	free_list(shell->token_list);
	shell->token_list = list;
}