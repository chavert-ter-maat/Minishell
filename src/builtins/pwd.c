#include "../../include/minishell.h"

void ft_pwd(t_shell *shell, char **arguments)
{
	char *buffer;

	buffer = NULL;
  	buffer = getcwd(buffer, sizeof(buffer));
	if(buffer == NULL)
	    perror_exit("pwd: ");	
    else 
       	write(STDOUT_FILENO, buffer, ft_strlen(buffer));
		write(STDOUT_FILENO, "\n", 1);
	free(buffer);
}
