#include "../../include/minishell.h"

static char	*get_var_name(t_shell *shell, char *var)
{
	char	*name;
	int		index;

	if (!var)
		return (NULL);
	index = 0;
	while (var[index] && var[index] != '=')
		index++;
	name = ft_substr(var, 0, (index));
	if(!name)
		shell_error(shell, malloc_error, "get_var_name", 1);
	return(name);
}
static char	*get_var_value(t_shell *shell, char *var)
{
	char	*value;
	int		start;
	int		end;

	if (!var)
		return (NULL);
	start = 0;
	end = 0;
	while(var[start] && var[start] != '=')
		start++;
	while (var[end])
		end++;
	value = NULL;
	value = ft_substr(var, (start + 1), (end - 1));
	if(!value)
		shell_error(shell, malloc_error, "get_env_value", 1);
	return(value);
}

int	add_var_to_environment(t_shell *shell, char *var)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	name = get_var_name(shell, var);
	if (!name)
		return (-1);
	value = get_var_value(shell, var);
	if (!value)
	{
		free(name);
		return (-1);
	}
	env_set_var_value1(shell, name, value);
	return (0);
}

void	init_env(t_shell *shell, char **envp)
{
	int		index;

	shell->environment = list_create(shell, sizeof(t_var), free_var, comp_var);
	if (!shell->environment)
		exit(EXIT_FAILURE);
	shell->envp = envp;
	index = 0;
	while(envp[index])
	{
		if (add_var_to_environment(shell, envp[index++]) != 0)
		{
			shell->return_value = 1;
			clean_exit(shell);
		}
	}
}