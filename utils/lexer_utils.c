#include "../include/minishell.h"

t_token	*list_add_token(t_token *top, t_token *new)
{
	t_token	*temp;

	temp = top;
	if (!temp)
		return (new);
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (top);
}

t_token	*new_token(t_shell *shell)
{
	t_token	*new;

	new = 0;
	new = malloc(sizeof(t_token));
	if (!new)
		(void) shell;//free and exit;
	new->type = TOKEN;
	new->str = NULL;
	new->next = NULL;
	return (new);
}

void	print_list(t_token *list)
{
	t_token	*temp;

	temp = list;
	while (temp)
	{
		printf("%s\n", temp->str);
		temp = temp->next;
	}
}

t_token	*free_list(t_token *list)
{
	t_token	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp->str);
		free(temp);
	}
	return (NULL);
}
