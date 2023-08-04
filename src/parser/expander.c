/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 13:32:00 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/02 19:57:24 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*list_get_expand_var(t_shell *shell, char *str, size_t *i)
{
	size_t	save_i;
	char *	var_name;

	save_i = *i;
	*i = 0;
	find_end_var(&(str[save_i]), i, VAR);
	*i += save_i++;
	var_name = ft_strndup(&(str[save_i]), *i - save_i);
	if (!var_name)
		shell_error(shell, malloc_error, "exp_str()", 1), free(str);
	return (var_name);
}

/* splits the string in WORDS and VAR tokens,
expands the VARs to their value and adds them
to the list */

static void	expand_str(t_shell *shell, t_list *list, char *str)
{
	size_t	i;
	char	*var_name;

	i = 0;
	if (str[i] == '\0')
		list_add_new_word(shell, list, str, &i);
	while (str[i] && shell->token_list)
	{
		if (str[i] != '$')
			list_add_new_word(shell, list, str, &i);
		else
		{
			var_name = list_get_expand_var(shell, str, &i);
			printf("CHeck %s\n", var_name);
			if (!var_name)
				return (free(str));
			list_add_expand_var(shell, list, var_name);
			free(var_name);
		}
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
		expand_str(shell, list, str);
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
			return (free_list(list));
		current = current->next;
	}
	return (list);
}

void	expander(t_shell *shell)
{
	t_list	*list;

	if (!shell->token_list)
		return ;
	list = list_create(shell, sizeof(t_token), free_token, comp_token);
	list = expand_token_list(shell, list);
	list_cat_words(shell, list);
	free_list(shell->token_list);
	shell->token_list = list;
}
