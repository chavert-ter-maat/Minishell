#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <string.h>
# include <termios.h>
# include <errno.h>
# include <stdbool.h>
# include "../libft/libft.h"

typedef enum e_token_type {
	TOKEN = 0,
	PIPE,
	QUOTE,
	DQUOTE,
	GREAT,
	LESS,
	VAR,
	SPACE,
	WORD
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	char	*cmd_line;
	t_token	*tokens;
}	t_shell;

void			tok_type_pipe(char *cmd_line, size_t *pos, t_token_type type);
void			tok_type_quote(char *cmd_line, size_t *pos, t_token_type type);
void			tok_type_redir(char *cmd_line, size_t *pos, t_token_type type);
void			tok_type_var(char *cmd_line, size_t *pos, t_token_type type);
void			tok_type_consec(char *cmd_line, size_t *pos, t_token_type type);
t_token_type	get_char_type(char c);
t_token			*list_add_token(t_token *top, t_token *new);
t_token			*new_token(t_shell *shell);
void			print_list(t_token *list);
t_token			*free_list(t_token *list);
t_token			*lexer(t_shell *shell);

#endif