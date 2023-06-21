#include "../../include/minishell.h"

/* like strcat() but the string str1 does not need to have
sufficient space to hold the result */

char	*ft_append(char *str1, char *str2)
{
	char	*append;
	size_t	size;

	if (!str2)
		return(str1);
	if (!str1)
		return(str2);
	append = NULL;
	size = ft_strlen(str1) + ft_strlen(str2) + 1;
	append = malloc(size);
	if (!append)
	{
		free(str1);
		return (NULL);
	}
	append[0] = '\0';
	ft_strlcat(append, str1, size);
	ft_strlcat(append, str2, size);
	free(str1);
	return (append);
}

/* checks the list and if two censecutive tokens are of type WORD
it concatenates the words in the first token string,
removes the second token from the list and frees that token
remaining the order of the rest of the list */

t_token	*list_cat_words(t_shell *shell, t_token *top)
{
	t_token	*temp;
	t_token	*to_free;

	if (!top)
		return (NULL);
	temp = top;
	while (temp->next)
	{
		if (temp->type == WORD &&temp->next->type == WORD)
		{
			temp->str = ft_append(temp->str, temp->next->str);
			if (!temp->str)
				error_free_exit(shell);
			to_free = temp->next;
			temp->next = temp->next->next;
			free(to_free->str);
			free(to_free);
		}
		else
		temp = temp->next;
	}
	return (top);
}

/* allocates a copy of the token and adds
it to the back of the list */

t_token	*list_add_copy(t_shell *shell, t_token *top, t_token *token)
{
	t_token	*new;

	if (!token)
		return(top);
	new = new_token(shell);
	new->type = token->type;
	if (!token->str)
		return(list_add_token(top, new));
	new->str = ft_strdup(token->str);
	if (!new->str)
	{
		free(new);
		error_free_exit(shell);
	}
	return (list_add_token(top, new));
}

/* returns last nde in list */

t_token *list_last(t_token *top)
{
	t_token *temp;
	
	if (!top)
		return (NULL);
	temp = top;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

char *find_var_value(t_var *var_list, char *var) //ADD $? !!!!!!!!!!!!!!!!!!!!!!!
{
	t_var	*temp;
	size_t	len;

	if (!var)
		return (NULL);
	len = 0;
	tok_type_var(var, &len, VAR);
	var++;
	temp = var_list;
	while (temp)
	{
		if (ft_strncmp(var, temp->name, len) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

t_token	*list_new_word(t_shell *shell, t_token *top, char *str, size_t *i)
{
	t_token	*new;
	size_t	save_i;

	new = malloc(sizeof(t_token));
	if (!new)
		error_free_exit(shell);
	new->type = WORD;
	new->next = NULL;
	save_i = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	new->str = ft_strndup(&(str[save_i]), *i - save_i);
	if (!new->str)
	{
		free(new);
		error_free_exit(shell);
	}
	return (list_add_token(top, new));
}