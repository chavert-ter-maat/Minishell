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
# define ERROR		1
# define TRUE		1
# define FALSE		0
 
// enums
typedef enum e_token_type {

	TOKEN = 0,
	PIPE,
	QUOTE,
	DQUOTE,
	GREAT,
	LESS,
	VAR,
	E_SPACE,
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

// functions

typedef	void(*func_ptr_free)(void *);
typedef int(*func_ptr_comp)(void *, void *);


//structs
typedef struct s_node
{
	void			*data;
	struct s_node	*next;
}	t_node;

typedef struct s_list
{
	size_t			data_size;
	int				count;
	t_node			*head;
	t_node			*tail;
	func_ptr_free	ft_free;
	func_ptr_comp	ft_comp;
} t_list;

typedef struct s_token
{
	t_token_type	type;
	char			*str;
}	t_token;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
}	t_redir;

typedef struct s_command
{
	char	**args;
	t_list	*arg_list;
	t_list	*redir_list;
}	t_command;

typedef struct s_executor
{	
  	int 		temp_stdin;
	int 		temp_stdout;
	int			argc;
	char		**argv;
	}	t_executor;

typedef struct s_var
{
	char			*name;
	char			*value;
}	t_var;

typedef struct s_shell
{
	int					return_value;
	char				*cmd_line;
	struct s_builtins	*builtins;
	char				**envp;
	t_list				*command_list;
	t_list				*environment;
  	t_executor	 		*executor;
	t_list				*token_list;
}	t_shell;

typedef struct s_builtins
{
	const char	*type_builtin;
	void		(*function)(t_shell *shell, char **arguments);
}	t_builtins;

// lexer
void	lexer(t_shell *shell);
int		get_token_type(char c);
void	find_end_pipe(char *cmd_line, size_t *i, int type);
void	find_end_quote(char *cmd_line, size_t *i, int type);
void	find_end_redir(char *cmd_line, size_t *i, int type);
void	find_end_var(char *cmd_line, size_t *i, int type);
void	find_end_consec(char *cmd_line, size_t *i, int type);

//expander
void	expander(t_shell *shell);
char 	*expand_var(t_shell *shell, char *name);
void	list_cat_words(t_shell *shell, t_list *list);
void	list_add_new_word(t_shell *shell, t_list *list, char *str, size_t *i);
void	list_add_token_copy(t_shell *shell, t_list *list, t_token *token);
void	list_add_expand_var(t_shell *shell, t_list *list, char *var_name);


//parser
void	parser(t_shell *shell);
void	make_command_table(t_shell *shell);
void	skip_space(t_node **node);
t_node	*add_cmd_arg(t_shell *shell, t_node *node, t_command *new);
t_node	*add_cmd_redir(t_shell *shell, t_node *node, t_command *new_cmd);
t_node	*skip_token(t_shell *shell, t_node *node, t_command *new);
char	**arg_list_to_array(t_command *command);

// utils
void	return_to_promt(t_shell *shell);
void	free_shell(t_shell *shell);
void	shell_error(t_shell *shell, void (*func)(const char *, const char *),
				const char *str1, const char *str2, int ret);
void	print_error(const char *str1, const char *str2);
void	malloc_error(const char *str1, const char *str2);
void	syntax_error(const char *str1, const char *str2);
void 	dir_error(const char *str1, const char *str2);
void	too_little_args(const char *str1, const char *str2);
void	too_many_args(const char *str1, const char *str2);
void	exit_numeric_arg(const char *str1, const char *str2);
void	dir_unset(const char *str1, const char *str2);
void	export_error(const char *str1, const char *str2);

//test functions
void	print_command_table(t_shell *shell);
void	print_token_list(t_shell *shell);

// executor
void	executor(t_shell *shell);
void	execute_non_builtin(t_shell *shell, t_command *command);
void	handle_multiple_commands(t_shell *shell);
void	handle_single_command(t_shell *shell, t_command *command);
int		ft_here_doc(char *delimiter, int fd_write_end);


void	print_status_waidpid(pid_t pid, int options);
void	infile_as_stdin(t_shell *shell);
void	outfile_as_stdout(t_shell *shell);
void	input_error(void);
void	error_exit(t_shell *shell, char *input);
void	error_exit_fork(t_shell *shell, char *input);
void	error_no_command(t_shell *shell, char *argv);
void	error_perm_denied(t_shell *shell, char *cmd);

// environment
t_var 	*create_new_node(char *new_var_variable);
void	init_env(t_shell *shell, char **varp);
void	print_environment(t_list *environment);
void	env_set_var_value1(t_shell *shell, char *name, char *value);
void	env_set_var_value2(t_shell *shell, char *not_allocated_name, char *value);
char 	*env_get_var_value(t_shell *shell, char *name);
int		add_var_to_environment(t_shell *shell, char *var);


// builtin cd
void	cd_path(t_shell *shell, char *path, char *oldpwd);
void	cd_home(t_shell *shell, char *oldpwd);
void	cd_dir_up(t_shell *shell, char *oldpwd);
void	cd_oldpwd(t_shell *shell, char *oldpwd);
void	cd_error(char *argument);
void	ft_cd(t_shell *shell, t_command *command);
void	cd_stay(t_shell *shell, char *oldpwd);

// builtins
void	ft_echo(char **args, int fd);
void 	ft_env(t_shell *shell, t_command *command);
void	ft_export(t_shell *shell, t_command *command);
int		check_if_builtin(char *command);
void	execute_builtin(t_shell *shell, t_command *command);
void	ft_pwd(t_shell *shell);
void	ft_unset(t_shell *shell, t_command *command);
void	ft_exit(t_shell *shell, t_command *command);
void	clean_exit(t_shell *shell);

//signals
void	init_signals(void);
void	sigquit_handler(t_shell *shell);
void	sigint_handler(int signum);

//generic list
t_list	*list_create(t_shell *shell, size_t data_size, func_ptr_free ft_free, func_ptr_comp ft_comp);
void	list_add_new_node(t_shell *shell, t_list *list, void *data);
void	list_remove_head(t_list *list);
void	list_remove_node(t_list *list, void *data);
int		list_get_index(t_list *list, void *data);
void	list_remove_index(t_list *list, int index);
bool	list_contains(t_list *list, void *data);
bool	list_is_identical(t_list *list1, t_list *list2);
t_node	*list_get_node(t_list *list, void *data);

//generic list free functions
void	free_node_data(func_ptr_free ft_free, void *data);
t_list	*free_list(t_list *list);
void	free_token(void *data);
void	free_command(void *data);
void	free_redir(void *data);
void	free_var(void *data);
void	free_arg(void *data);

//generic list compare functions
int		comp_command(void *data1, void *data2);
int		comp_arg(void *data1, void *data2);
int		comp_redir(void *data1, void *data2);
int		comp_token(void *data1, void *data2);
int		comp_var(void *data, void *comp_name);

#endif