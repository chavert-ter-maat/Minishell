#include "../../include/minishell.h"

int	go_path(t_shell *shell, char *path, char *cwd) // niet uitvoeren wanneer geen chdir

{
	char *pwd;

	pwd = NULL;
	cd_update_env(shell, "OLDPWD", cwd);
	if (chdir(path) == FAILED)
		return (ERROR);
	pwd = getcwd(pwd, 0); //malloc!
	if(!pwd)
	{
		free(pwd);
		return(ERROR);
	}
	cd_update_env(shell, "PWD", pwd); // check
	return (SUCCESS);
}

int	go_home_dir(t_shell *shell, char *cwd)
{
	char	*home_path;

	home_path = get_path(shell, "HOME");
	if (!home_path)
		return(ERROR);
	cd_update_env(shell, "OLDPWD", cwd);
	if (chdir(home_path) == FAILED) // free cwd?
		return (ERROR);
	cd_update_env (shell, "PWD", home_path);
	return(SUCCESS);
}

int	go_previous_dir(t_shell *shell, char *cwd)
{
	int		str_len;
	char	*new_path;

	new_path = NULL;
	str_len = ft_strlen(cwd) - 1;
	while (cwd[str_len])
	{
		if (cwd[str_len] == '/')
		{
			new_path = ft_strndup(cwd, str_len); //MALLOC!!
			break ;
		}
		str_len--;
	}
	if (!new_path)
		return (ERROR);
	cd_update_env(shell, "OLDPWD", cwd); //niet uitvoeren wanneer geen chdir
	if (chdir(new_path) == FAILED)
		return (ERROR);
	cd_update_env(shell, "PWD", new_path);
	return (SUCCESS);
}

int	go_oldpwd(t_shell *shell, char *cwd) 
{
	char	*oldpwd;

	oldpwd = get_path(shell, "OLDPWD");
	ft_putstr_fd("\n ", 1);
	ft_putstr_fd("oldpwd =", 1);
	ft_putstr_fd(oldpwd, 1);
	ft_putstr_fd("\n", 1);
	if (chdir(oldpwd) == FAILED)
		return (ERROR);
	cd_update_env(shell, "PWD", oldpwd);  
	cd_update_env(shell, "OLDPWD", cwd);
	return (SUCCESS);
}
