#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
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
# include <sys/errno.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"

// defines
# define WRITE_END	1
# define READ_END	0
# define SUCCESS	0
# define FOUND		1
# define NOT_FOUND	0
# define FAILED		-1
# define ERROR		-1
# define TRUE		1
# define FALSE		0
 
// structs
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

typedef enum e_redir_type 
{
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

typedef struct s_argument
{
	char				*str;
	struct s_argument	*next;
}	t_argument;

typedef struct s_command
{
	char				**args;
	struct s_argument	*arg_list;
	struct s_redir		*redir;
	struct s_command	*next;
}	t_command;

typedef struct s_executor
{	
  int temp_stdin;
	int temp_stdout;
	char		*cmd_line;
	int			argc;
	char		**argv;
	char		**envp;
	char		*infile;
	char		*outfile;
	int			pipe_infile[2];
}	t_executor;


typedef struct s_shell
{
  t_executor 	*executor;
	char		*cmd_line;
	t_token		*lexer;
	t_token		*expander;
	t_command	*parser;
	t_var		*var_list;
	char		**envp;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				is_set;
	struct	s_env	*next;
}	t_env;

typedef struct s_builtins
{
	const char	*type_builtin;
	void		(*function)(t_shell *shell, char **arguments);
}	t_builtins;

typedef struct s_shell
{
	int				return_value;
	char			*cmd_line;
	t_builtins 		*builtins;
	t_command		*command;
	t_env			*env_list;
  	t_executor	 	*executor;
	t_token			*expander;
	t_token			*lexer;
	t_var			*var_list;
}	t_shell;

void			tok_type_pipe(char *cmd_line, size_t *i, t_token_type type);
void			tok_type_quote(char *cmd_line, size_t *i, t_token_type type);
void			tok_type_redir(char *cmd_line, size_t *i, t_token_type type);
void			tok_type_var(char *cmd_line, size_t *i, t_token_type type);
void			tok_type_consec(char *cmd_line, size_t *i, t_token_type type);
t_token_type	find_metachar(char c);

// lexer
void		lexer(t_shell *shell);
void		tok_type_pipe(char *cmd_line, size_t *i, t_token_type type);
void		tok_type_quote(char *cmd_line, size_t *i, t_token_type type);
void		tok_type_redir(char *cmd_line, size_t *i, t_token_type type);
void		tok_type_var(char *cmd_line, size_t *i, t_token_type type);
void		tok_type_consec(char *cmd_line, size_t *i, t_token_type type);
int			find_metachar(char c);
void		list_add_token(t_token **top, t_token *new);
void		new_token(t_shell *shell, t_token **new);
char 		*find_var_value(t_var *var_list, char *var);

//expander
void		expander(t_shell *shell);
void		list_cat_words(t_shell *shell);
void		list_add_copy(t_shell *shell, t_token *token);
t_token		*list_last(t_token *top);
char		*ft_append(char *str1, char *str2);
void		list_new_word(t_shell *shell, char *str, size_t *i);

//parser
void		parser(t_shell *shell);
void		list_add_cmd(t_command **top, t_command *new);
t_command	*list_add_new_cmd(t_shell *shell);
void		skip_space(t_token **current);
void		list_add_redir(t_redir **top, t_redir *new);
void		list_add_arg(t_argument **top, t_argument *new);
t_token		*add_cmd_word(t_shell *shell, t_token *current, t_command *new);
t_token		*add_cmd_redir(t_shell *shell, t_token *current, t_command *new_cmd);
t_token		*add_cmd_skip(t_shell *shell, t_token *current, t_command *new);
char		**arg_list_to_array(t_command *cmd);

//
void		free_tok_list(t_token **list);
t_shell		*init_shell(void);
void		free_shell(t_shell *shell);
void		free_var_list(t_var **list);
void		free_cmd_list(t_command **list);
void		free_redir_list(t_redir	**list);
void		shell_error(void (*func)(const char *), const char *str);
void		print_error(const char *str);
void		malloc_error(const char *str);
void		syntax_error(const char *str);


// executor
void		run_command(t_shell *shell, char *argv);
void		create_single_child(t_shell *shell);
void		handle_multiple_commands(t_shell *shell, int nb_commands, char **argv);
void		input_handling(t_shell *shell, int argc, char **argv, char **envp);
void		print_status_waidpid(pid_t pid, int options);
void		infile_as_stdin(t_shell *shell);
void		outfile_as_stdout(t_shell *shell);
void		input_error(void);
void		error_exit(char *input);
void		perror_exit(char *input);
void		error_no_command(char *argv);

//test functions
void		print_list(t_token *list);
void		print_command_table(t_shell *shell);
void			tok_type_pipe(char *cmd_line, size_t *pos, t_token_type type);
void			tok_type_quote(char *cmd_line, size_t *pos, t_token_type type);
void			tok_type_redir(char *cmd_line, size_t *pos, t_token_type type);
void			tok_type_var(char *cmd_line, size_t *pos, t_token_type type);
void			tok_type_consec(char *cmd_line, size_t *pos, t_token_type type);
t_token_type	get_char_type(char c);

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

// executor
void	run_command(t_shell *shell, char *argv);
void	handle_multiple_commands(t_shell *shell, int nb_commands, char **argv);
void	create_single_child(t_shell *shell);
int		ft_here_doc(char *delimiter, int fd_write_end);
// void	input_handling(t_shell *shell, int argc, char **argv, char **envp);
void	print_status_waidpid(pid_t pid, int options);
void	infile_as_stdin(t_shell *shell);
void	outfile_as_stdout(t_shell *shell);
void	input_error(void);
void	error_exit(char *input);
void	perror_exit(char *input);
void	error_no_command(char *argv);

// environment
t_env	*init_env(char **envp);
void	print_list_env(t_env *env_list);
void	free_list_env(t_env *env_list);
void	add_node_to_list_env(t_env **env_list, t_env *new_node);

// builtins
void	ft_echo(char **args, int fd);
int		ft_env(t_shell *shell);
int		execute_builtins(t_shell *shell, char **arguments);
int		ft_pwd(void);
void	ft_unset(t_command *command, t_env **env_list);

#endif