/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_jumptable.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 14:58:43 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/24 17:58:52 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	find_end_pipe(char *cmd_line, size_t *i, int type)
{
	(void) cmd_line;
	(void) type;
	(*i)++;
}

void	find_end_quote(char *cmd_line, size_t *i, int type)
{
	(*i)++;
	while (cmd_line[*i] && get_token_type(cmd_line[*i]) != type)
		(*i)++;
	(*i)++;
}

void	find_end_redir(char *cmd_line, size_t *i, int type)
{
	(*i)++;
	if (cmd_line[*i] && get_token_type(cmd_line[*i]) == type)
		(*i)++;
}

void	find_end_var(char *cmd_line, size_t *i, int type)
{
	(void) type;
	(*i)++;
	if (cmd_line[*i] == '?')
	{
		(*i)++;
		return ;
	}
	if (cmd_line[*i] && (ft_isalpha(cmd_line[*i]) || cmd_line[*i] == '_'))
		(*i)++;
	while (cmd_line[*i] && (ft_isalnum(cmd_line[*i]) \
	|| cmd_line[*i] == '_'))
		(*i)++;
}

void	find_end_consec(char *cmd_line, size_t *i, int type)
{
	(*i)++;
	while (cmd_line[*i] && get_token_type(cmd_line[*i]) == type)
		(*i)++;
}
