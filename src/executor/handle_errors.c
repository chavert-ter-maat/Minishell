/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_errors.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:13:39 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/25 14:35:39 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	perror_update_status(t_shell *shell, char *input_name)
{
	perror(input_name);
	shell->status = 1;
}

void	perror_exit_fork(t_shell *shell, char *input)
{
	perror(input);
	ft_putstr_fd("failed\n", STDERR_FILENO);
	free_shell(shell);
	_exit(1);
}

void	error_no_command(t_shell *shell, char *cmd)
{
	ft_putstr_fd("shellyeah: ", STDERR_FILENO);
	if (cmd != NULL)
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("command not found\n", STDERR_FILENO);
	free_shell(shell);
	_exit(127);
}

void	error_perm_denied(t_shell *shell, char *cmd)
{
	ft_putstr_fd("shellyeah: ", STDERR_FILENO);
	if (cmd != NULL)
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("Permission denied\n", STDERR_FILENO);
	free_shell(shell);
	_exit(126);
}
