#include "../../include/minishell.h"

/* like strcat() but the string str1 does not need to have
sufficient space to hold the result */

static char	*ft_append(char *str1, char *str2)
{
	char	*append;
	size_t	size;

	if (!str2)
		return(str1);
	if (!str1)
		return(str2);
	size = ft_strlen(str1) + ft_strlen(str2) + 1;
	append = ft_calloc(size, sizeof(char));
	if (!append)
		return (free(str1), NULL);
	append[0] = '\0';
	ft_strlcat(append, str1, size);
	ft_strlcat(append, str2, size);
	return (free(str1), append);
}

/* if two censecutive tokens are of type WORD
it concatenates the words in the first token string,
removes the second token from the list and frees that token
remaining the order of the rest of the list */

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
				return (shell_error(shell, malloc_error, "list_cat_words()", 1));
			list_remove_node(list, next_token);
		}
		else
		temp = temp->next;
	}
}

char *expand_var(t_shell *shell, char *name)
{
	char	*value;

	if (!name)
		return (NULL);
	if (name[0] == '?')
		value = ft_itoa(shell->return_value);
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
	t_token	new;
	size_t	save_i;

	new.type = WORD;
	save_i = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	new.str = ft_strndup(&(str[save_i]), *i - save_i);
	if (!new.str)
		return (shell_error(shell, malloc_error, "list_add_new_word()", 1));
	list_add_new_node(shell, list, &new);
}

void	list_add_token_copy(t_shell *shell, t_list *list, t_token *token)
{
	t_token new;

	new.type = token->type;
	new.str = ft_strdup(token->str);
	if (!new.str)
		return(shell_error(shell, malloc_error, "expander()", 1));
	list_add_new_node(shell, list, &new);
}