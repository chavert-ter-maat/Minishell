/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_builtins.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:17:28 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/16 15:17:29 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_builtin(t_shell *shell, t_command *command)
{
	if (ft_strncmp(command->args[0], "cd", 3) == 0)
		return (ft_cd(shell, command));
	if (ft_strncmp(command->args[0], "echo", 5) == 0)
		return (ft_echo(command->args, 1));
	if (ft_strncmp(command->args[0], "env", 4) == 0)
		return (ft_env(shell, command));
	if (ft_strncmp(command->args[0], "export", 7) == 0)
		return (ft_export(shell, command));
	if (ft_strncmp(command->args[0], "pwd", 4) == 0)
		return (ft_pwd(shell));
	if (ft_strncmp(command->args[0], "unset", 6) == 0)
		return (ft_unset(shell, command));
	if (ft_strncmp(command->args[0], "exit", 5) == 0)
		return (ft_exit(shell, command));
}

int	check_if_builtin(char *command)
{
	if (ft_strncmp(command, "cd", 3) == 0)
		return (TRUE);
	if (ft_strncmp(command, "echo", 5) == 0)
		return (TRUE);
	if (ft_strncmp(command, "env", 4) == 0)
		return (TRUE);
	if (ft_strncmp(command, "export", 7) == 0)
		return (TRUE);
	if (ft_strncmp(command, "pwd", 4) == 0)
		return (TRUE);
	if (ft_strncmp(command, "unset", 6) == 0)
		return (TRUE);
	if (ft_strncmp(command, "exit", 5) == 0)
		return (TRUE);
	return (FALSE);
}
