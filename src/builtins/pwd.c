#include "../../include/minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd && errno == ENOENT)
		pwd = ft_strdup(env_get_var_value(shell, "PWD"));
	else if (!pwd)
	{
		perror(NULL);
		g_status = 1;
	}
	if (!pwd)
		return (shell_error(shell, malloc_error, "ft_pwd", NULL, 1));
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
	free(pwd);
	g_status = 0;
}
