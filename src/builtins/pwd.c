#include "../../include/minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd && errno == ENOENT)
		pwd = ft_strdup(env_get_var_value(shell, "PWD"));
	else if (!pwd)
		return ;
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
	free(pwd);
}
