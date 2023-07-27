#include "../../include/minishell.h"

void	cd_error(char *argument)
{
	ft_putstr_fd("cd: no such file or directory:",1);
	ft_putstr_fd(argument, 1);
	ft_putchar_fd('\n', 1);
}

static int	check_argument(t_shell *shell, char *argument, char *cwd)
{
	if(!argument)
		return (go_home_dir(shell, cwd));
	if (ft_strncmp(argument, ".", 2) == 0)
		return (SUCCESS);
	if (ft_strncmp(argument, "..", 3) == 0)
		return (go_previous_dir(shell, cwd));
	if (ft_strncmp(argument, "-", 2) == 0)
		return (go_oldpwd(shell));
	else
		return(go_path(shell, argument, cwd));
	return(ERROR);
}	

void	ft_cd(t_shell *shell, t_command *command)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if(!cwd)
		return ;
	if(check_argument(shell, command->args[1], cwd) == ERROR)
	{
		cd_error(command->args[1]);
		free(cwd);
	}
}
