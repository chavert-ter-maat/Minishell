#include "../../include/minishell.h"

void ft_pwd(t_shell *shell)
{
	char *cwd;
	
	cwd = NULL;
	cwd = getcwd(cwd, 0); //malloc!
	if(!cwd)
	{
		free(cwd);
		error_exit_fork(shell, "cwd: ");
	}
	write(STDOUT_FILENO, cwd, ft_strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	free(cwd);
}
