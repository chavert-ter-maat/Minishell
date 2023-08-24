/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:18:08 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/24 12:18:31 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_exit(t_shell *shell)
{
	shell->environment = free_list(shell->environment);
	free_shell(shell);
	exit(shell->status);
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
	ft_putendl_fd("exit", 0);
	if (command->arg_list->count == 1)
	{
		shell->status = 0;
		clean_exit(shell);
	}
	if (numeric(command->args[1]) == false)
	{
		shell_error(shell, exit_numeric_arg, command->args[1], 255);
		clean_exit(shell);
	}
	if (command->arg_list->count > 2)
	{
		shell_error(shell, print_error, "exit: too many arguments", 1);
		return ;
	}
	else
	{
		shell->status = ft_atoi(command->args[1]) % 256;
		if (shell->status < 0)
			shell->status += 256;
		clean_exit(shell);
	}
}
