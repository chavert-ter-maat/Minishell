#include "../../include/minishell.h"

static t_builtins find_buildin_function(char *cmd)
{
	int	index;
	index = 0;

	static const t_builtins	jump_table[] = 
	{
	{.name_builtin = "cd", .name_function = ft_cd},
	{.name_builtin = "echo", .name_function = ft_echo},
	{.name_builtin = "export", .name_function = ft_export},
	{.name_builtin = "pwd", .name_function = ft_pwd},
	{.name_builtin = "unset", .name_function = ft_unset},
	{.name_builtin = "env", .name_function = ft_env},
	{.name_builtin = "exit", .name_function = ft_exit},
	{NULL, NULL}
	};
	while(jump_table[index] && strncmp(jump_table[index].name_builtin), cmd,
		ft_strlen(cmd) + 1);
		index++;
	return(jump_table[index]);
}

void	execute_builtins(t_shell *shell, char **argument)
{
	t_builtins builtin_function;

	if(argument == NULL || *argument == NULL)
		return(ERROR);
	builtin_function = find_builtin_function(argument[0]);
	if(builtin_function == NULL)
		return(ERROR);
	builtin_function.name_function();
}