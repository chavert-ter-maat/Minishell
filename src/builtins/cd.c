#include "../../include/minishell.h"


static void	check_argument(t_shell *shell, char *argument, char *oldpwd)
{
	if (!argument || ft_strncmp(argument, "~", 2) == 0)
		cd_home(shell, oldpwd);
	else if (ft_strncmp(argument, ".", 2) == 0)
		cd_stay(shell, oldpwd);
	else if (ft_strncmp(argument, "..", 3) == 0)
		cd_previous_dir(shell, oldpwd);
	else if (ft_strncmp(argument, "-", 2) == 0)
		cd_oldpwd(shell, oldpwd);
	else
		cd_path(shell, argument, oldpwd);
}

void	ft_cd(t_shell *shell, t_command *command)
{
	char	*oldpwd;

	oldpwd = NULL;
	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd) //kunnen we hier dan perror gebruiken??
		return ;
	check_argument(shell, command->args[1], oldpwd);
}
