/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:16:25 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/24 15:35:14 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_var_name(t_shell *shell, char *var, char **name)
{
	int		i;

	if (!var)
		return (0);
	i = 0;
	if (!var[i] || (!ft_isalpha(var[i]) && var[i] != '_'))
		return (0);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	*name = ft_substr(var, 0, (i));
	if (!*name)
		shell_error(shell, malloc_error, "get_var_name", 1);
	return (1);
}

static int	get_var_value(t_shell *shell, char *var, char **value)
{
	int		start;
	int		end;

	if (!var)
		return (0);
	start = 0;
	end = 0;
	while (var[start] && var[start] != '=')
		start++;
	if (var[start] != '=')
		return (0);
	while (var[end])
		end++;
	*value = ft_substr(var, (start + 1), (end - start));
	if (!*value)
		shell_error(shell, malloc_error, "get_env_value", 1);
	return (1);
}

int	add_var_to_environment(t_shell *shell, char *var)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	if (!get_var_name(shell, var, &name))
		return (shell_error(shell, export_error, var, 1), -1);
	if (!name)
		return (-1);
	if (get_var_value(shell, var, &value))
	{
		if (!value)
			return (free(name), -1);
	}
	env_set_var_value1(shell, name, value);
	return (0);
}

static void	set_env(t_shell *shell)
{
	t_var	*var;
	t_node	*target;
	int		shlvl;

	target = list_get_node(shell->environment, "OLDPWD");
	if (target)
	{
		var = (t_var *)target->data;
		free(var->value);
		var->value = NULL;
	}
	target = list_get_node(shell->environment, "SHLVL");
	if (target)
	{
		var = (t_var *)target->data;
		shlvl = ft_atoi(var->value);
		shlvl++;
		free(var->value);
		var->value = ft_itoa(shlvl);
		if (!var->value)
		{
			shell_error(shell, print_error, "failed to initialize shell", 1);
			clean_exit(shell);
		}
	}
}

void	init_env(t_shell *shell, char **envp)
{
	int		index;

	shell->environment = list_create(shell, sizeof(t_var), free_var, comp_var);
	if (!shell->environment)
	{
		shell_error(shell, print_error, "failed to initialize shell", 1);
		exit(EXIT_FAILURE);
	}
	index = 0;
	while (shell->environment && envp[index])
	{
		if (add_var_to_environment(shell, envp[index++]) != 0)
		{
			shell_error(shell, print_error, "failed to initialize shell", 1);
			clean_exit(shell);
		}
	}
	if (!shell->environment)
		clean_exit(shell);
	set_env(shell);
}
