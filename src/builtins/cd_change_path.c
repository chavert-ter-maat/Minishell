#include "../../include/minishell.h"

int	go_path(t_shell *shell, char *path, char *cwd)

{
	char *pwd;

	pwd = NULL;
	if (chdir(path) == FAILED)
		return (ERROR);
	pwd = getcwd(pwd, 0);
	if(!pwd)
	{
		free(cwd);
		return(ERROR);
	}
    env_set_var_value2(shell, "OLDPWD", cwd);
    env_set_var_value2(shell, "PWD", pwd);
	return (SUCCESS);
}

int	go_home_dir(t_shell *shell, char *cwd)
{
	char	*home_path;

	home_path = env_get_var_value(shell, "HOME");
	if (!home_path || chdir(home_path) == FAILED)
    {
        free(cwd);
        if (home_path)
            free(home_path);
		return (ERROR);
    }
    env_set_var_value2(shell, "OLDPWD", cwd);
    env_set_var_value2(shell, "PWD", home_path);
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
			new_path = ft_strndup(cwd, str_len);
			break ;
		}
		str_len--;
	}
	if (!new_path || chdir(new_path) == FAILED)
    {
        free(cwd);
        if (new_path)
            free(new_path);
		return (ERROR);
    }
    env_set_var_value2(shell, "OLDPWD", cwd);
    env_set_var_value2(shell, "PWD", new_path);
	return (SUCCESS);
}

int	go_oldpwd(t_shell *shell) 
{
	char	*oldpwd;
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	oldpwd = env_get_var_value(shell, "OLDPWD");
	if (!pwd || ! oldpwd || chdir(oldpwd) == FAILED)
	{
        if (pwd)
    		free(pwd);
        if (oldpwd)
            free(oldpwd);
		return (ERROR);
	}
    env_set_var_value2(shell, "OLDPWD", pwd);
    env_set_var_value2(shell, "PWD", oldpwd);
	return (SUCCESS);
}
