#include "../../include/minishell.h"

/* increments i by one */

void	find_end_pipe(char *cmd_line, size_t *i, int type)
{
	(void) cmd_line;
	(void) type;
	(*i)++;
}

/* changes i to the end of the quotes or end of line */

void	find_end_quote(char *cmd_line, size_t *i, int type)
{
	(*i)++;
	while (cmd_line[*i] && get_token_type(cmd_line[*i]) != type)
		(*i)++;
	(*i)++;
}

/* changes i to the end of a redirecting operator */

void	find_end_redir(char *cmd_line, size_t *i, int type)
{
	(*i)++;
	if (cmd_line[*i] && get_token_type(cmd_line[*i]) == type)
		(*i)++;
}

/* changes i to the end of a variable or the end of "$?".
A variable name starts with an underscore or alphabetical character and
consists of underscores alphabetical characters and numbers */

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

/* changes i to the end of consecutive white space 
or consecutive 'word characters' */

void	find_end_consec(char *cmd_line, size_t *i, int type)
{
	(*i)++;
	while (cmd_line[*i] && get_token_type(cmd_line[*i]) == type)
		(*i)++;
}
