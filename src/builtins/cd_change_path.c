// #include "../../include/minishell.h"

// int	go_path(t_shell *shell, char *path, char *cwd)

// {
// 	char *pwd;

// 	pwd = NULL;
// 	if (chdir(path) == FAILED)
// 		return (ERROR);
// 	pwd = getcwd(pwd, 0);
// 	if(!pwd)
// 	{
// 		free(pwd);
// 		return(ERROR);
// 	}
// 	cd_update_env(shell, "OLDPWD", cwd);
// 	cd_update_env(shell, "PWD", pwd); 
// 	free(pwd);
// 	return (SUCCESS);
// }

// int	go_home_dir(t_shell *shell, char *cwd)
// {
// 	char	*home_path;

// 	home_path = get_path(shell, "HOME");
// 	if (!home_path)
// 		return(ERROR);
// 	if (chdir(home_path) == FAILED)
// 		return (ERROR);
// 	cd_update_env(shell, "OLDPWD", cwd);
// 	cd_update_env (shell, "PWD", home_path);
// 	return(SUCCESS);
// }

// int	go_previous_dir(t_shell *shell, char *cwd)
// {
// 	int		str_len;
// 	char	*new_path;

// 	new_path = NULL;
// 	str_len = ft_strlen(cwd) - 1;
// 	while (cwd[str_len])
// 	{
// 		if (cwd[str_len] == '/')
// 		{
// 			new_path = ft_strndup(cwd, str_len);
// 			break ;
// 		}
// 		str_len--;
// 	}
// 	if (chdir(new_path) == FAILED)
// 	{
// 		free(new_path);
// 		return (ERROR);
// 	}
// 	cd_update_env(shell, "OLDPWD", cwd);
// 	cd_update_env(shell, "PWD", new_path);
// 	free(new_path);
// 	return (SUCCESS);
// }

// int	go_oldpwd(t_shell *shell) 
// {
// 	char	*oldpwd;
// 	char	*pwd;

// 	pwd = NULL;
// 	pwd = getcwd(pwd, 0);
// 	if(!pwd)
// 	{
// 		free(pwd);
// 		return(ERROR);
// 	}
// 	oldpwd = get_path(shell, "OLDPWD");
// 	if (chdir(oldpwd) == FAILED)
// 	{
// 		free(pwd);
// 		return (ERROR);
// 	}
// 	cd_update_env(shell, "OLDPWD", pwd);
// 	cd_update_env(shell, "PWD", oldpwd);
// 	free(pwd);
// 	return (SUCCESS);
// }
