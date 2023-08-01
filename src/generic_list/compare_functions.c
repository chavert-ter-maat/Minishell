#include "../../include/minishell.h"

int	comp_token(void *data1, void *data2)
{
	t_token *token1;
	t_token	*token2;

	if (!data1 || !data2)
		return (-1);
	token1 = (t_token*) data1;
	token2 = (t_token*) data2;
	if (token1->type != token2->type)
		return (-1);
	return (ft_strcmp(token1->str, token2->str));
}

int	comp_command(void *data1, void *data2)
{
	t_command	*command1;
	t_command	*command2;

	if (!data1 || !data2)
		return (-1);
	command1 = (t_command*) data1;
	command2 = (t_command*) data2;
	if (list_is_identical(command1->arg_list, command2->arg_list) == false)
		return (-1);
	if (list_is_identical(command1->redir_list, command2->redir_list) == false)
		return (-1);
	return (0);
}

int	comp_arg(void *data1, void *data2)
{
	const char	**arg1;
	const char	**arg2;

	if (!data1 || !data2)
		return (-1);
	arg1 = (const char **) data1;
	arg2 = (const char **) data2;
	return (ft_strcmp(*arg1, *arg2));
}

int		comp_redir(void *data1, void *data2)
{
	t_redir *redir1;
	t_redir	*redir2;

	if (!data1 || !data2)
		return (-1);
	redir1 = (t_redir*) data1;
	redir2 = (t_redir*) data2;
	if (redir1->type != redir2->type)
		return (-1);
	return (ft_strcmp(redir1->file, redir2->file));
}

int	comp_var(void *data, void *comp_name)
{
	t_var	*var;
	char	*name;

	if (!data || !comp_name)
		return (-1);
	var = (t_var *) data;
	name = (char *) comp_name;
	return (ft_strcmp(var->name, name));
}