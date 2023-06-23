#include "../../include/minishell.h"

/* increments i by one */

void	tok_type_pipe(char *cmd_line, size_t *i, t_token_type type)
{
	(void) cmd_line;
	(void) type;
	(*i)++;
}

/* changes i to the end of the quotes or end of line */

void	tok_type_quote(char *cmd_line, size_t *i, t_token_type type)
{
	(*i)++;
	while (cmd_line[*i] && find_metachar(cmd_line[*i]) != type)
		(*i)++;
	(*i)++;
}

/* changes i to the end of a redirecting operator */

void	tok_type_redir(char *cmd_line, size_t *i, t_token_type type)
{
	(*i)++;
	if (cmd_line[*i] && find_metachar(cmd_line[*i]) == type)
		(*i)++;
}

/* changes i to the end of a variable or the end of "$?".
A variable name starts with an underscore or alphabetical character and
consists of underscores alphabetical characters and numbers */

void	tok_type_var(char *cmd_line, size_t *i, t_token_type type)
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

/* changes i to the end of consecutive white space 
or consecutive 'word characters' */

void	tok_type_consec(char *cmd_line, size_t *i, t_token_type type)
{
	(*i)++;
	while (cmd_line[*i] && find_metachar(cmd_line[*i]) == type)
		(*i)++;
}
