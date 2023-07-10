#include "../../include/minishell.h"

int ft_pwd(void)
{
	char *buffer;

	buffer = NULL;
  	buffer = getcwd(buffer, sizeof(buffer));
	if(buffer == NULL)
	    perror_exit("pwd: ");
	write(STDOUT_FILENO, buffer, ft_strlen(buffer));
	write(STDOUT_FILENO, "\n", 1);
	free(buffer);
	return(SUCCES);
}
