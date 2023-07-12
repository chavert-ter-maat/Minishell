#include "../../include/minishell.h"

void	list_add_token(t_token **top, t_token *new)
{
	t_token	*temp;

	if (!*top)
		*top = new;
	else
	{
		temp = *top;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	new_token(t_shell *shell, t_token **new)
{
	*new = ft_calloc(1, sizeof(t_token));
	if (!*new)
		return (shell_error(malloc_error, "new_token() @ ft_calloc"), free_shell(shell));
	(*new)->type = TOKEN;
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

