/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:13:49 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/16 15:14:00 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executor(t_shell *shell)
{
	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, sigint_handler);
	if (!shell->command_list || shell->command_list->count == 0)
		return ;
	if (shell->command_list->count == 1)
		handle_single_command(shell, shell->command_list->head->data);
	else
		handle_multiple_commands(shell);
	return ;
}
