#include "../../include/minishell.h"

void	shell_error(void (*func)(const char *), const char *str) //errno status update toevoegen
{
	ft_putstr_fd("shellyeah: ", 2);
	func(str);
}

void	syntax_error(const char *str)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("'", 2);
}

void	print_error(const char *str)
{
	ft_putendl_fd(str, 2);
}

void	malloc_error(const char *str)
{
	ft_putstr_fd("Memory allocation failed in ", 2);
	ft_putendl_fd(str, 2);
}