#include "../../include/minishell.h"

typedef void	(*t_token_type_func)(char *, size_t *, t_token_type);

/*
get_char_type checks if the given character is a meta character
or whitespace or part of a WORD.
*/

t_token_type	get_char_type(char c)
{
	const char		set[] = "x|\'\"><$";
	size_t			pos;

	pos = 1;
	while (pos <= 6)
	{
		if (set[pos] == c)
			return (pos);
		pos++;
	}
	if (c == ' ' || c == '\t' || c == '\n')
		return (pos);
	pos++;
	return (pos);
}

/*
Get_token_info gets the data for the string in the token structure.
It uses a jumptable.
*/

void	get_token_info(t_token *token, char *cmd_line, size_t *pos)
{
	const t_token_type_func	func[9] = {
	[0] = NULL,
	[1] = &tok_type_pipe,
	[2] = &tok_type_quote,
	[3] = &tok_type_quote,
	[4] = &tok_type_redir,
	[5] = &tok_type_redir,
	[6] = &tok_type_var,
	[7] = &tok_type_consec,
	[8] = &tok_type_consec,
	};
	size_t					save_pos;

	save_pos = *pos;
	token->type = get_char_type(cmd_line[*pos]);
	func[token->type](cmd_line, pos, token->type);
	token->str = ft_strndup(&(cmd_line[save_pos]), *pos - save_pos);
}

// for testing puropses

void	exit_lexer(t_shell *shell)
{
	print_list(shell->tokens);
	shell->tokens = free_list(shell->tokens);
}

/*
The lexer function takes the command line input
and returns a linked list of tokens.
*/

t_token	*lexer(t_shell *shell)
{
	t_token	*new;
	size_t	pos;

	pos = 0;
	while (shell->cmd_line[pos])
	{
		new = new_token(shell);
		get_token_info(new, shell->cmd_line, &pos);
		shell->tokens = list_add_token(shell->tokens, new);
	}
	exit_lexer(shell);//remove later
	return (shell->tokens);
}
