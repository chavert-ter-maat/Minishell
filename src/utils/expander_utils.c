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
	size = ft_strlen(str1) + ft_strlen(str2) + 1;
	append = ft_calloc(size, sizeof(char));
	if (!append)
		return (free(str1), NULL);
	append[0] = '\0';
	ft_strlcat(append, str1, size);
	ft_strlcat(append, str2, size);
	return (free(str1), append);
}

void	remove_token_from_list(t_token *previous, t_token *token)
{
	previous->next = token->next;
	if ((token)->str)
		free((token)->str);
	free(token);
}

/* checks the expander list and removes type TOKEN tokens,
if two censecutive tokens are of type WORD
it concatenates the words in the first token string,
removes the second token from the list and frees that token
remaining the order of the rest of the list */

void	list_cat_words(t_shell *shell)
{
	t_token	*temp;

	if (!shell->expander)
		return ;
	temp = shell->expander;
	while (temp->next)
	{
		if (temp->next->type == TOKEN)
			remove_token_from_list(temp, temp->next);
		else if (temp->type == WORD &&temp->next->type == WORD)
		{
			temp->str = ft_append(temp->str, temp->next->str);
			if (!temp->str)
				return (shell_error(malloc_error, "list_cat_words() @ ft_append"), free_shell(shell));
			remove_token_from_list(temp, temp->next);
		}
		else
		temp = temp->next;
	}
}

/* allocates a copy of the token and adds
it to the back of the expander list */

void	list_add_copy(t_shell *shell, t_token *token)
{
	t_token	*new;

	if (!token)
		return ;
	new_token(shell, &new);
	if (!new)
		return ;
	new->type = token->type;
	new->str = ft_strdup(token->str);
	list_add_token(&(shell->expander), new);
	if (!new->str)
		return (shell_error(malloc_error, "list_add_copy() @ ft_strdup"), free_shell(shell));
}

/* returns last node in list */

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

void	list_new_word(t_shell *shell, char *str, size_t *i)
{
	t_token	*new;
	size_t	save_i;

	new_token(shell, &new);
	if (!new)
		return ;
	new->type = WORD;
	save_i = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	new->str = ft_strndup(&(str[save_i]), *i - save_i);
	list_add_token(&(shell->expander), new);
	if (!new->str)
		return (shell_error(malloc_error, "list_new_word() @ ft_strndup"), free_shell(shell));
}