/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_errors.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:13:39 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/17 11:40:10 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	perror_return_promt(char *input_name)
{
	perror(input_name);
	g_status = errno;
	return ;
}

void	perror_exit_fork(t_shell *shell, char *input)
{
	perror(input);
	ft_putstr_fd("failed\n", STDERR_FILENO);
	free_shell(shell);
	_exit(errno);
}

void	error_no_command(t_shell *shell, char *cmd)
{
	ft_putstr_fd("Shell_yeah: ", STDERR_FILENO);
	if (cmd != NULL)
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("command not found\n", STDERR_FILENO);
	free_shell(shell);
	_exit(127);
}

void	error_perm_denied(t_shell *shell, char *cmd)
{
	ft_putstr_fd("Shell_yeah: ", STDERR_FILENO);
	if (cmd != NULL)
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("permission denied\n", STDERR_FILENO);
	free_shell(shell);
	_exit(127);
}
