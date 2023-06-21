#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
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
	TOKEN = -1,
	PIPE,
	QUOTE,
	DQUOTE,
	GREAT,
	LESS,
	VAR,
	SPACE,
	WORD
}	t_token_type;

typedef enum e_redir_type {
	REDIR = 0,
	IN,
	OUT,
	HEREDOC,
	APPEND,
}	t_redir_type;

typedef struct s_token
{
	t_token_type	type;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}	t_var;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char				*command;
	char				**args;
	struct s_redir		*redir;
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	char	*cmd_line;
	t_token	*lexer;
	t_token	*expander;
	t_var	*var_list;
}	t_shell;

void			tok_type_pipe(char *cmd_line, size_t *i, t_token_type type);
void			tok_type_quote(char *cmd_line, size_t *i, t_token_type type);
void			tok_type_redir(char *cmd_line, size_t *i, t_token_type type);
void			tok_type_var(char *cmd_line, size_t *i, t_token_type type);
void			tok_type_consec(char *cmd_line, size_t *i, t_token_type type);
t_token_type	find_metachar(char c);
t_token			*list_add_token(t_token *top, t_token *new);
t_token			*new_token(t_shell *shell);
void			print_list(t_token *list);
void			free_list(t_token *list);
t_token			*lexer(t_shell *shell);
t_shell			*init_shell(void);
t_token			*list_cat_words(t_shell *shell, t_token *list);
t_token			*list_add_copy(t_shell *shell, t_token *top, t_token *token);
t_token			*expander(t_shell *shell);
char			*ft_append(char *str1, char *str2);
t_token 		*list_last(t_token *top);
char 			*find_var_value(t_var *var_list, char *var);
void			error_free_exit(t_shell *shell);
t_token			*list_new_word(t_shell *shell, t_token *top, char *str, size_t *i);

#endif