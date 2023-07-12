#include "../../include/minishell.h"

static t_builtins *find_function(char *cmd)
{
	int	index;
	index = 0;

	static const t_builtins	jump_table[] = 
	{
	// {.type_builtin = "cd", .function = ft_cd},
	{.type_builtin = "echo", .function = ft_echo},
	// {.type_builtin = "export", .function = ft_export},
	{.type_builtin = "pwd", .function = ft_pwd},
	{.type_builtin = "unset", .function = ft_unset},
	{.type_builtin = "env", .function = ft_env},
	// {.type_builtin = "exit", .function = ft_exit},
	{NULL, NULL}
	};
	while(jump_table[index] && strncmp(jump_table[index].type_builtin), cmd,
		ft_strlen(cmd) + 1);
		index++;
	return(jump_table[index]);
}

int	execute_builtins(t_shell *shell, char **arguments)
{
	t_builtins *builtin_function;

	if(arguments == NULL || *arguments == NULL)
		return(ERROR); 
	builtin_function = find_function(arguments[0]);
	if(builtin_function == NULL)
		return(ERROR);
	builtin_function->function(shell, arguments);
	return(SUCCESS);
}