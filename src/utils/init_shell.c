/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_shell.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:55:01 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/16 15:55:08 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_status;

void	init_shell(t_shell *shell, char **envp)
{
	ft_bzero(shell, sizeof(t_shell));
	g_status = 0;
	init_env(shell, envp);
}
