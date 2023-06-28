#include "../../include/minishell.h"

void	expand_var(t_shell *shell, char *var_name)
{
	t_token *new;
	char	*value;

	new_token(shell, &new);
	if (!new)
		return ;
	list_add_token(&(shell->expander), new);
	value = find_var_value(shell->var_list, var_name);
	if (!value)
		return ;
	new->type = WORD;
	new->str = ft_strdup(value);
	if (!new->str)
		return (shell_error(malloc_error, "expand_var() @ ft_strdup"), free_shell(shell));
}

/* splits the string in WORDS and VAR tokens,
expands the VARs to their value and adds them
to the expander list */

void	split_str_in_tokens(t_shell *shell, char *str)
{
	size_t	i;
	size_t	save_i;
	char	*var;

	i = 0;
	while(str[i])
	{
		save_i = i;
		if (str[i] != '$')
			list_new_word(shell, str, &i);
		else
		{
			i = 0;
			tok_type_var(&(str[save_i]), &i, VAR);
			i += save_i;
			var = ft_strndup(&(str[save_i]), i - save_i);
			if (!var)
				return (shell_error(malloc_error, "split_str_in_tokens() @ ft_strndup")), free(str), free_shell(shell);
			free(var);
		}
		if (!shell->expander)
			break ;
	}
	free(str);
}

void	expand_quote(t_shell *shell, char *quote)
{
	t_token *new;
	size_t	len;

	len = ft_strlen(quote);
	if (len < 2 || quote[len - 1] != '\'')
		return (shell_error(print_error, "unclosed quotes"), free_shell(shell));
	new_token(shell, &new);
	if (!new)
		return ;
	new->type = WORD;
	quote++;
	new->str = ft_strndup(quote, ft_strlen(quote) - 1);
	list_add_token(&(shell->expander), new);
	if (!new->str)
		return (shell_error(malloc_error, "expand_quote() @ ft_strndup"), free_shell(shell));
}

void	expand_dquote(t_shell *shell, char *quote)
{
	size_t	len;
	char	*str;

	len = ft_strlen(quote);
	if (len < 2 || quote[len - 1] != '\"')
		return (shell_error(print_error, "unclosed quotes"), free_shell(shell));
	quote++;
	str = ft_strndup(quote, ft_strlen(quote) - 1);
	if (!str)
		return (shell_error(malloc_error, "expand_dquote() @ ft_strndup"), free_shell(shell));
	split_str_in_tokens(shell, str);
}

void expander(t_shell *shell)
{
	t_token	*current;

	current = shell->lexer;
	while (current)
	{
		if (current->type == QUOTE)
			expand_quote(shell, current->str);
		else if (current->type == DQUOTE)
			expand_dquote(shell, current->str);
		else if (current->type == VAR)
			expand_var(shell, current->str);
		else
			list_add_copy(shell, current);
		if (shell->expander == NULL)
			return;
		current = current->next;
	}
	list_cat_words(shell);
	free_tok_list(&(shell->lexer));
}