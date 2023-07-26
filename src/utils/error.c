#include "../../include/minishell.h"

void	shell_error(t_shell *shell, void (*func)(const char *), const char *str, int ret)
{
	shell->return_value = ret;
	ft_putstr_fd("shellyeah: ", 2);
	func(str);
	free_shell(shell);
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