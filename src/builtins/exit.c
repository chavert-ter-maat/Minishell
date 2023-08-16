/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:18:08 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/16 15:46:28 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_exit(t_shell *shell)
{
	shell->environment = free_list(shell->environment);
	free_shell(shell);
	exit(g_status);
}

static bool	numeric(char *str)
{
	size_t	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit(t_shell *shell, t_command *command)
{
	if (command->arg_list->count == 1)
	{
		g_status = 0;
		clean_exit(shell);
	}
	if (numeric(command->args[1]) == false)
	{
		shell_error(shell, exit_numeric_arg, command->args[1], 255);
		clean_exit(shell);
	}
	if (command->arg_list->count > 2)
	{
		shell_error(shell, too_many_args, "exit", 1);
		return ;
	}
	else
	{
		g_status = ft_atoi(command->args[1]) % 256;
		if (g_status < 0)
			g_status += 256;
		clean_exit(shell);
	}
}
