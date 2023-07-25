#include "../../include/minishell.h"

int ft_pwd(void)
{
	char *cwd;
	
	cwd = NULL;
	cwd = getcwd(cwd, 0); //malloc!
	if(!cwd)
	{
		free(cwd);
		perror_exit("cwd: ");
	}
	write(STDOUT_FILENO, cwd, ft_strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	free(cwd);
	return(SUCCESS);
}
