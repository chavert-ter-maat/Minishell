#include "../../include/minishell.h"

void	free_node_data(func_ptr_free ft_free, void *data)
{
	if (ft_free)
		ft_free(data);
	else
		free(data);
}

t_list	*free_list(t_list *list)
{
	t_node	*temp;

	if (!list)
		return (NULL);
	temp = list->head;
	while (temp)
	{
		list->head = list->head->next;
		free_node_data(list->ft_free, temp->data);
		free(temp);
		temp = list->head;
	}
	free(list);
	return (NULL);
}

void	free_token(void *data)
{
		t_token	*token;

		if (!data)
			return;
		token = (t_token *) data;
		if (token->str)
		{
			free(token->str);
			token->str = NULL;
		}
		free(token);
		token = NULL;
}

void	free_command(void *data)
{
		t_command	*command;

		if (!data)
			return;
		command = (t_command *) data;
		if (command->arg_list)
			command->arg_list = free_list(command->arg_list);
		if (command->redir_list)
			command->redir_list = free_list(command->redir_list);
		if (command->args)
		{
			free(command->args);
			command->args = NULL;
		}
		free(command);
		command = NULL;
}

void	free_redir(void *data)
{
	t_redir	*redir;

	if (!data)
		return;
	redir = (t_redir *) data;
	if (redir->file)
	{
		free(redir->file);
		redir->file = NULL;
	}
	free(redir);
	redir = NULL;
}