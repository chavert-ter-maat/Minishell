#include "../../include/minishell.h"

void	list_add_cmd(t_command **top, t_command *new)
{
	t_command	*temp;

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

t_command	*list_add_new_cmd(t_shell *shell)
{
	t_command	*new;

	new = ft_calloc(1, sizeof(t_command));
	if (!new)
		return (shell_error(malloc_error, "list_add_new_cmd() @ ft_calloc"), free_shell(shell), NULL);
	list_add_cmd(&(shell->command), new);
	return (new);
}

void	skip_space(t_token **current)
{
	while (*current && ((*current)->type == TOKEN || (*current)->type == SPACE))
		*current = (*current)->next;
}

void	list_add_redir(t_redir **top, t_redir *new)
{
	t_redir	*temp;

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

void	list_add_arg(t_argument **top, t_argument *new)
{
	t_argument	*temp;

	if (!*top)
	{
		*top = new;
		new->str = ft_strtolower(new->str);
	}
	else
	{
		temp = *top;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}
