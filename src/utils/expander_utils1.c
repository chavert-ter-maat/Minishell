/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils1.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 14:56:42 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/24 17:59:22 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	list_cat_words(t_shell *shell, t_list *list)
{
	t_node	*temp;
	t_token	*token;
	t_token	*next_token;

	if (!list || !list->head)
		return ;
	temp = list->head;
	while (temp->next)
	{
		token = (t_token *) temp->data;
		next_token = (t_token *) temp->next->data;
		if (token->type == WORD && next_token->type == WORD)
		{
			token->str = ft_append(token->str, next_token->str);
			if (!token->str)
				return (shell_error(shell, malloc_error,
						"list_cat_words()", 1));
			list_remove_node(list, next_token);
		}
		else
			temp = temp->next;
	}
}

char	*expand_var(t_shell *shell, char *name)
{
	char	*value;

	if (!name)
		return (NULL);
	if (name[0] == '\0' || name[0] == '?')
	{
		if (name[0] == '\0')
			value = ft_strdup("$");
		else
			value = ft_itoa(shell->status);
		if (!value)
			shell_error(shell, malloc_error, "expand_var", 1);
		return (value);
	}
	else
		value = env_get_var_value(shell, name);
	if (!value)
		return (value);
	value = ft_strdup(value);
	if (!value)
		shell_error(shell, malloc_error, "expand_var()", 1);
	return (value);
}

void	list_add_new_word(t_shell *shell, t_list *list, char *str, size_t *i)
{
	t_token	*new;
	size_t	save_i;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (shell_error(shell, malloc_error, "list_add_expand_var", 1));
	new->type = WORD;
	save_i = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	new->str = ft_strndup(&(str[save_i]), *i - save_i);
	if (!new->str)
		return (free(new), shell_error(shell, malloc_error,
				"list_add_new_word()", 1));
	if (list_add_new_node(shell, list, new))
		free(new);
	else
		free_token(new);
}

void	list_add_expand_var(t_shell *shell, t_list *list, char *var_name)
{
	t_token	*new;

	(void) var_name;
	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (shell_error(shell, malloc_error, "list_add_expand_var", 1));
	new->str = expand_var(shell, var_name);
	new->type = WORD;
	if (!new->str)
		return (free(new));
	if (list_add_new_node(shell, list, new))
		free(new);
	else
		free_token(new);
}

void	list_add_token_copy(t_shell *shell, t_list *list, t_token *token)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (shell_error(shell, malloc_error, "list_add_token_copy", 1));
	new->type = token->type;
	new->str = ft_strdup(token->str);
	if (!new->str)
		return (free(new), shell_error(shell, malloc_error, "expander()", 1));
	if (list_add_new_node(shell, list, new))
		free(new);
	else
		free_token(new);
}
