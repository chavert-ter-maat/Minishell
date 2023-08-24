/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:20:16 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/24 11:50:16 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	check_argument(t_shell *shell, char *argument, char *pwd)
{
	if (!argument || ft_strncmp(argument, "~", 2) == 0)
		cd_home(shell, pwd);
	else if (ft_strncmp(argument, ".", 2) == 0)
		cd_stay(shell, pwd);
	else if (ft_strncmp(argument, "..", 3) == 0)
		cd_dir_up(shell, pwd);
	else if (ft_strncmp(argument, "-", 2) == 0)
		cd_oldpwd(shell, pwd);
	else
		cd_path(shell, argument, pwd);
}

void	ft_cd(t_shell *shell, t_command *command)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd && errno == ENOENT)
		pwd = ft_strdup(env_get_var_value(shell, "PWD"));
	if (!pwd)
	{
		if (errno == ENOENT)
			return (perror_update_status(shell, "malloc"));
		else
			return (perror_update_status(shell, "getcwd"));
	}
	check_argument(shell, command->args[1], pwd);
}
