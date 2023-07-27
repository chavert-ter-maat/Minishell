#include "../../include/minishell.h"

void	cd_error(char *argument)
{
	ft_putstr_fd("cd: no such file or directory:",1);
	ft_putstr_fd(argument, 1);
	ft_putchar_fd('\n', 1);
}
