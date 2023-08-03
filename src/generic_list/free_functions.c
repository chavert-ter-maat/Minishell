#include "../../include/minishell.h"

void	free_token(void *data)
{
	t_token	*token;

	if (!data)
		return ;
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
		return ;
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
		return ;
	redir = (t_redir *) data;
	if (redir->file)
	{
		free(redir->file);
		redir->file = NULL;
	}
	free(redir);
	redir = NULL;
}

void	free_var(void *data)
{
	t_var	*var;

	if (!data)
		return ;
	var = (t_var *) data;
	if (var->name)
		free(var->name);
	if (var->value)
		free(var->value);
	free(var);
	var = NULL;
}

void	free_arg(void *data)
{
	char	**arg;

	if (!data)
		return ;
	arg = (char **) data;
	if (*arg)
		free(*arg);
	free(arg);
	arg = NULL;
}
