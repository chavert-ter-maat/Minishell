#include "../../include/minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell->cmd_line)
	{
		free(shell->cmd_line);
		shell->cmd_line = NULL;
	}
	free_tok_list(&(shell->lexer));
	free_tok_list(&(shell->expander));
	free_var_list(&(shell->var_list));
	free_cmd_list(&(shell->parser));
}

void	free_tok_list(t_token **list)
{
	t_token	*temp;

	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		if (temp->str)
		{
			free(temp->str);
			temp->str = NULL;
		}
		free(temp);
	}
}

void	free_var_list(t_var **list)
{
	t_var	*temp;

	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		// if (temp->name)			deze staan nu uit omdat ik ze bij het testen
		// 	free(temp->name);		niet gemalloct heb..
		// if (temp->value)
		// 	free(temp->value);
		free(temp);
	}
}

void	free_redir_list(t_redir	**list)
{
	t_redir	*temp;

	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		if (temp->file)
			free(temp->file);
		free(temp);
	}
}

void	free_arg_list(t_argument	**list)
{
	t_argument	*temp;

	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		if (temp->str)
			free(temp->str);
		free(temp);
	}
}

void	free_cmd_list(t_command **list)
{
	t_command	*temp;

	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		if (temp->command)
			free(temp->command);
		free_arg_list(&(temp->args));
		free_redir_list(&(temp->redir));
		free(temp);
	}
}