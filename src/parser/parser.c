/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 13:29:49 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/03 13:35:32 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

typedef t_node	*(*t_add_cmd_func)(t_shell *, t_node *, t_command *);

char	**arg_list_to_array(t_command *command)
{
	char	**args;
	char	**arg;
	t_node	*temp;
	int		i;

	args = ft_calloc(command->arg_list->count + 1, sizeof(char *));
	i = 0;
	if (args && command->arg_list)
	{
		temp = command->arg_list->head;
		while (temp)
		{
			arg = (char **) temp->data;
			if (i == 0)
				ft_strtolower(*arg);
			args[i] = *arg;
			temp = temp->next;
			i++;
		}
	}
	return (args);
}

static t_node	*fill_command(t_shell *shell, t_node *node, t_command *new)
{
	const t_add_cmd_func	func[9] = {
	[0] = &skip_token,
	[1] = &skip_token,
	[2] = NULL,
	[3] = NULL,
	[4] = &add_cmd_redir,
	[5] = &add_cmd_redir,
	[6] = NULL,
	[7] = &skip_token,
	[8] = &add_cmd_arg,
	};
	t_token					*token;

	if (node)
		token = (t_token *) node->data;
	while (shell->token_list && node && token->type != PIPE)
	{
		node = func[token->type](shell, node, new);
		if (node)
			token = (t_token *) node->data;
	}
	if (shell->token_list && node)
		node = func[token->type](shell, node, new);
	return (node);
}

void	skip_space(t_node **node)
{
	t_token	*token;

	if (!*node)
		return ;
	token = (t_token *)(*node)->data;
	while (token && token->type == E_SPACE)
	{
		*node = (*node)->next;
		if (*node)
			token = (t_token *)(*node)->data;
		else
			return ;
	}
}

static void	add_cmd(t_shell *shell, t_node **node)
{
	t_token		*token;
	t_command	new;

	skip_space(node);
	if (!*node)
		return ;
	token = (t_token *)(*node)->data;
	if (token->type == PIPE)
		return (shell_error(shell, syntax_error, token->str, NULL, 258));
	new.arg_list = list_create(shell, sizeof(char *), free_arg, comp_arg);
	new.redir_list = list_create(shell, sizeof(t_redir),
			free_redir, comp_redir);
	*node = fill_command(shell, *node, &new);
	new.args = arg_list_to_array(&new);
	list_add_new_node(shell, shell->command_list, &new);
}

void	make_command_table(t_shell *shell)
{
	t_node		*node;

	if (!shell->token_list)
		return ;
	shell->command_list = list_create(shell, sizeof(t_command),
			free_command, comp_command);
	if (!shell->command_list)
		return ;
	node = shell->token_list->head;
	while (shell->command_list && node)
		add_cmd(shell, &node);
}
