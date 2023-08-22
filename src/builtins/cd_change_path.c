#include "../../include/minishell.h"

void	cd_path(t_shell *shell, char *path, char *oldpwd)
{
	char	*pwd;

	pwd = NULL;
	if (chdir(path) == FAILED)
	{
		perror(NULL);
		shell->status = 1;
		return (free(oldpwd));
	}
	pwd = getcwd(pwd, 0);
	if (!pwd)
	{
		perror(NULL);
		shell->status = 1;
		return ;
	}
	env_set_var_value2(shell, "OLDPWD", oldpwd);
	env_set_var_value2(shell, "PWD", pwd);
	shell->status = 0;
}

void	cd_home(t_shell *shell, char *oldpwd)
{
	char	*home_path;

	home_path = env_get_var_value(shell, "HOME");
	if (!home_path)
		return (free(oldpwd), shell_error(shell, dir_unset, "HOME", 1));
	if (chdir(home_path) == FAILED)
	{
		perror("chdir");
		shell->status = 1;
		return (free(oldpwd));
	}
	home_path = ft_strdup(home_path);
	if (!home_path)
	{
		shell_error(shell, malloc_error, "cd_home", 1);
		return (free(oldpwd));
	}
	env_set_var_value2(shell, "OLDPWD", oldpwd);
	env_set_var_value2(shell, "PWD", home_path);
	shell->status = 0;
}

void	cd_dir_up(t_shell *shell, char *oldpwd)
{
	int		str_len;
	char	*pwd;

	pwd = NULL;
	str_len = ft_strlen(oldpwd);
	while (oldpwd[--str_len])
	{
		if (oldpwd[str_len] == '/')
		{
			pwd = ft_strndup(oldpwd, str_len);
			break ;
		}
	}
	if (!pwd)
		return (free(oldpwd), shell_error(shell, malloc_error,
				"cd_previous_dir", 1));
	if (chdir(pwd) == FAILED)
	{
		perror(NULL);
		shell->status = 1;
		return (free(oldpwd), free(pwd));
	}
	env_set_var_value2(shell, "OLDPWD", oldpwd);
	env_set_var_value2(shell, "PWD", pwd);
	shell->status = 0;
}

void	cd_oldpwd(t_shell *shell, char *oldpwd)
{
	char	*pwd;

	pwd = env_get_var_value(shell, "OLDPWD");
	if (!pwd)
		return (free(oldpwd), shell_error(shell, dir_unset, "OLDPWD", 1));
	if (chdir(pwd) == FAILED)
	{
		perror(NULL);
		shell->status = 1;
		return (free(oldpwd));
	}
	pwd = ft_strdup(pwd);
	if (!pwd)
		return (free(oldpwd), shell_error(shell, malloc_error, "cd_oldpwd", 1));
	ft_putendl_fd(pwd, 1);
	env_set_var_value2(shell, "OLDPWD", oldpwd);
	env_set_var_value2(shell, "PWD", pwd);
	shell->status = 0;
}

void	cd_stay(t_shell *shell, char *oldpwd)
{
	char	*pwd;

	pwd = ft_strdup(oldpwd);
	if (!pwd)
		return (free(oldpwd), shell_error(shell, malloc_error, "cd_stay", 1));
	env_set_var_value2(shell, "OLDPWD", oldpwd);
	env_set_var_value2(shell, "PWD", pwd);
	shell->status = 0;
}
