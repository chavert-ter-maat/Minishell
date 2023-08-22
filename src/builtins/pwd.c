/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:17:33 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/22 13:19:15 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd && errno == ENOENT)
		pwd = ft_strdup(env_get_var_value(shell, "PWD"));
	else if (!pwd)
	{
		perror(NULL);
		shell->status = 1;
	}
	if (!pwd)
		return (shell_error(shell, malloc_error, "ft_pwd", 1));
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
	free(pwd);
	shell->status = 0;
}
