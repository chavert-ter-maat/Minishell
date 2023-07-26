#include "../../include/minishell.h"

static int  check_n_flag(char *str)
{
	int index;
	int str_length;
	index = 2;
	str_length = ft_strlen(str);
	if(!str)
		return(NOT_FOUND);
	if(ft_strncmp(str, "-n", 2) == 0)
		{
			while(index < str_length)
			{
				if(ft_strncmp(&str[index], "n", 1) != 0 )
					return(NOT_FOUND);
				index++;
			}
		return(FOUND);
		}
	else
		return(NOT_FOUND);
}
void ft_echo(char **args, int fd)
{
	int n_flag;
	int index1;
	n_flag = 0;
	index1 = 1;
	while(check_n_flag(args[index1]) == FOUND)
		{
			n_flag = FOUND;
			index1++;
		}
	while(args[index1])
	{
		if(args[index1])
			ft_putstr_fd(args[index1], fd);
		if(args[index1 + fd])
			ft_putchar_fd(' ', fd);
		index1++;
	}
	if (n_flag == NOT_FOUND)
		ft_putchar_fd('\n', fd);
}
