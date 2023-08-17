/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_change_path.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:19:57 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/17 14:56:47 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cd_path(t_shell *shell, char *path, char *oldpwd)
{
	char	*pwd;

	pwd = NULL;
	if (chdir(path) == FAILED)
	{
		free(oldpwd);
		perror_exit_fork(shell, "chdir");
	}
	pwd = getcwd(pwd, 0);
	if (!pwd)
	{
		free(oldpwd);
		perror_exit_fork(shell, "getcwd");
	}
	env_set_var_value2(shell, "OLDPWD", oldpwd);
	env_set_var_value2(shell, "PWD", pwd);
	_exit(0);
}

void	cd_home(t_shell *shell, char *oldpwd)
{
	char	*home_path;

	home_path = env_get_var_value(shell, "HOME");
	if (!home_path)
	{
		free(oldpwd);
		shell_error(shell, dir_unset, "HOME", 1);
		_exit(1);
	}
	if (chdir(home_path) == FAILED)
	{
		free(oldpwd);
		perror_exit_fork(shell, "chdir");
	}
	home_path = ft_strdup(home_path);
	if (!home_path)
	{
		free(oldpwd);
		perror_exit_fork(shell, "malloc");
	}
	env_set_var_value2(shell, "OLDPWD", oldpwd);
	env_set_var_value2(shell, "PWD", home_path);
	_exit(0);
}

void	cd_dir_up(t_shell *shell, char *oldpwd)
{
	char *pwd;

	pwd = get_dir_up(oldpwd);
	if (!pwd)
	{
		free(oldpwd);
		perror_exit_fork(shell, "malloc");
	}
	if (chdir(pwd) == FAILED)
	{
		free(oldpwd);
		free(pwd);
		perror_exit_fork(shell, "chdir");
	}
	env_set_var_value2(shell, "OLDPWD", oldpwd);
	env_set_var_value2(shell, "PWD", pwd);
	_exit(0);
}

void	cd_oldpwd(t_shell *shell, char *oldpwd)
{
	char	*pwd;

	pwd = env_get_var_value(shell, "OLDPWD");
	if (!pwd)
	{
		free(oldpwd);
		shell_error(shell, dir_unset, "OLDPWD", 1);
		_exit(1);
	}
	if (chdir(pwd) == FAILED)
	{
		free(oldpwd);
		perror_exit_fork(shell, "chdir");
	}
	pwd = ft_strdup(pwd);
	if (!pwd)
	{
		free(oldpwd);
		perror_exit_fork(shell, "malloc");
	}
	ft_putendl_fd(pwd, 1);
	env_set_var_value2(shell, "OLDPWD", oldpwd);
	env_set_var_value2(shell, "PWD", pwd);
	_exit(0);
}

void	cd_stay(t_shell *shell, char *oldpwd)
{
	char	*pwd;

	pwd = ft_strdup(oldpwd);
	if (!pwd)
	{
		free(oldpwd);
		perror_exit_fork(shell, "malloc");
	}
	env_set_var_value2(shell, "OLDPWD", oldpwd);
	env_set_var_value2(shell, "PWD", pwd);
	_exit(0);
}
