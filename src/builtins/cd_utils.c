#include "../../include/minishell.h"

void	cd_error(char *argument)
{
	ft_putstr_fd("cd: no such file or directory:",1);
	ft_putstr_fd(argument, 1);
	ft_putchar_fd('\n', 1);
}

int	cd_update_env(t_shell *shell, char *name, char *new_path)
{
	int		str_len;
	t_env	*temp;

	temp = shell->env_list;
	str_len = ft_strlen(name) + 1; 
	while (shell->env_list) 
	{
		if (ft_strnstr(shell->env_list->name, name, str_len))
		{
			shell->env_list->value = new_path;
			shell->env_list = temp;
			return (SUCCESS);
		}
		shell->env_list = shell->env_list->next;
	}
	shell->env_list = temp;
	return (ERROR);
}


char	*get_path(t_shell *shell, char *name)
{
	char	*path;
	int		str_len;
	t_env	*temp;

	path = NULL;
	temp = shell->env_list;
	str_len = (ft_strlen(name) + 1); 
	while (shell->env_list) 
	{
		if (ft_strncmp(shell->env_list->name, name, str_len) == 0)
		{
			path = shell->env_list->value;
			shell->env_list = temp;
			return (path);
		}
		shell->env_list = shell->env_list->next;
	}
	shell->env_list = temp;
	return (NULL);
}

