#include "../../include/minishell.h"

t_token	*list_add_token(t_token *top, t_token *new)
{
	t_token	*temp;

	if (!new)
		return (top);
	if (!top)
		return (new);
	temp = top;
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
		error_free_exit(shell);
	new->type = TOKEN;
	new->str = NULL;
	new->next = NULL;
	return (new);
}

void	print_list(t_token *list) //can be removed later
{
	t_token	*temp;

	temp = list;
	while (temp)
	{
		printf("%s\n", temp->str);
		temp = temp->next;
	}
}

//klopt deze functie?? is het geen **list?
void	free_list(t_token *list)
{
	t_token	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->str)
			free(temp->str);
		free(temp);
	}
}
