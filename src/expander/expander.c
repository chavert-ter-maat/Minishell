#include "../../include/minishell.h"

t_token	*expand_var(t_shell *shell, t_token *top, char *var_name)
{
	t_token *new;
	char	*value;

	value = find_var_value(shell->var_list, var_name);
	if (!value)
		return (top);
	new = new_token(shell);
	new->type = WORD;
	new->str = ft_strdup(value);
	if (!new->str)
		error_free_exit(shell);
	top = list_add_token(top, new);
	return (top);
}

/* splits the string in WORDS and VAR tokens, adds them
to the list and also expands the VARs to their value */

t_token	*split_str_in_tokens(t_shell *shell, t_token *top, char *str)
{
	size_t	i;
	size_t	save_i;
	char	*var;

	i = 0;
	while(str[i])
	{
		print_list(shell->expander);
		save_i = i;
		if (str[i] != '$')
			top = list_new_word(shell, top, str, &i);
		else
		{
			i = 0;
			tok_type_var(&(str[save_i]), &i, VAR);
			i += save_i;
			var = ft_strndup(&(str[save_i]), i - save_i);
			if (!var)
				error_free_exit(shell);
			top = expand_var(shell, top, var);
			free(var);
		}
	}
	free(str);
	return (top);
}

t_token	*expand_quote(t_shell *shell, t_token *top, char *quote)
{
	t_token *new;
	size_t	len;

	len = ft_strlen(quote);
	if (len < 2 || quote[len - 1] != '\'')
		error_free_exit(shell); //how to handle unclosed quotes
	new = new_token(shell);
	new->type = WORD;
	quote++;
	new->str = ft_strndup(quote, ft_strlen(quote) - 1);
	top = list_add_token(top, new);
	if (!new->str)
		error_free_exit(shell);
	return(top);
}

t_token	*expand_dquote(t_shell *shell, t_token *top, char *quote)
{
	size_t	len;
	char	*str;

	len = ft_strlen(quote);
	if (len < 2 || quote[len - 1] != '\"')
		error_free_exit(shell); //how to handle unclosed quotes
	quote++;
	str = ft_strndup(quote, ft_strlen(quote) - 1);
	if (!str)
		error_free_exit(shell);
	top = split_str_in_tokens(shell, top, str);
	return(top);
}

t_token *expander(t_shell *shell)
{
	t_token	*top;
	t_token	*current;

	top = NULL;
	current = shell->lexer;
	while (current)
	{
		if (current->type == QUOTE)
			top = expand_quote(shell, top, current->str);
		else if (current->type == DQUOTE)
			top = expand_dquote(shell, top, current->str);
		else if (current->type == VAR)
			top = expand_var(shell, top, current->str);
		else
			top = list_add_copy(shell, top, current);
		current = current->next;
	}
	list_cat_words(shell, top);
	return (top);
}