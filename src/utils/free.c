/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 14:56:18 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/16 14:56:19 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell->cmd_line)
	{
		free(shell->cmd_line);
		shell->cmd_line = NULL;
	}
	shell->token_list = free_list(shell->token_list);
	shell->command_list = free_list(shell->command_list);
	ft_free_2d_array(&shell->envp);
}
