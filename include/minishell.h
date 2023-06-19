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
# include <sys/errno.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"

// defines
# define WRITE_END	1
# define READ_END	0
# define SUCCES		0
# define NOT_FOUND	0
# define FAILED		-1

// struckts
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

typedef struct s_executor
{
	int temp_stdin;
	int temp_stdout;
}	t_executor;

typedef struct s_shell
{
	char		*cmd_line;
	int			argc;
	char		**argv;
	char		**envp;
	char		*infile;
	char		*outfile;
	int			pipe_infile[2];
	t_token		*tokens;
	t_executor *executor;
}	t_shell;

// lexer
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

// executor
void	run_command(t_shell *shell, char *argv);
void	create_single_child(t_shell *shell);
void	handle_multiple_commands(t_shell *shell, int nb_commands, char **argv);
void	input_handling(t_shell *shell, int argc, char **argv, char **envp);
void	print_status_waidpid(pid_t pid, int options);
void	infile_as_stdin(t_shell *shell);
void	outfile_as_stdout(t_shell *shell);
void	input_error(void);
void	error_exit(char *input);
void	perror_exit(char *input);
void	error_no_command(char *argv);

#endif