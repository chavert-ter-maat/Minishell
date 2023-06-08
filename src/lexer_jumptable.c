#include "../include/minishell.h"

void	tok_type_pipe(char *cmd_line, size_t *pos, t_token_type type)
{
	(void) cmd_line;
	(void) type;
	(*pos)++;
}

void	tok_type_quote(char *cmd_line, size_t *pos, t_token_type type)
{
	(*pos)++;
	while (cmd_line[*pos] && get_char_type(cmd_line[*pos]) != type)
		(*pos)++;
	(*pos)++;
}

void	tok_type_redir(char *cmd_line, size_t *pos, t_token_type type)
{
	(*pos)++;
	if (cmd_line[*pos] && get_char_type(cmd_line[*pos]) == type)
		(*pos)++;
}

void	tok_type_var(char *cmd_line, size_t *pos, t_token_type type)
{
	(void) type;
	(*pos)++;
	if (cmd_line[*pos] == '?')
	{
		(*pos)++;
		return ;
	}
	if (cmd_line[*pos] && (ft_isalpha(cmd_line[*pos]) || cmd_line[*pos] == '_'))
		(*pos)++;
	while (cmd_line[*pos] && (ft_isalnum(cmd_line[*pos]) \
	|| cmd_line[*pos] == '_'))
		(*pos)++;
}

void	tok_type_consec(char *cmd_line, size_t *pos, t_token_type type)
{
	(*pos)++;
	while (cmd_line[*pos] && get_char_type(cmd_line[*pos]) == type)
		(*pos)++;
}
