#include "../../include/minishell.h"

void	shell_error(t_shell *shell, void (*func)(const char *, const char *),
		const char *str1, const char *str2, int ret)
{
	shell->return_value = ret;
	ft_putstr_fd("shellyeah: ", 2);
	func(str1, str2);
	free_shell(shell);
}

void	syntax_error(const char *str1, const char *str2)
{
	(void) str2;
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd("'", 2);
}

void	print_error(const char *str1, const char *str2)
{
	(void) str2;
	ft_putendl_fd(str1, 2);
}

void	malloc_error(const char *str1, const char *str2)
{
	(void) str2;
	ft_putstr_fd("Memory allocation failed in ", 2);
	ft_putendl_fd(str1, 2);
}

void	dir_error(const char *str1, const char *str2)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str2, 2);
	ft_putendl_fd(": No such file or directory", 2);
}

void	dir_unset(const char *str1, const char *str2)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str2, 2);
	ft_putendl_fd(" not set", 2);
}

void	too_little_args(const char *str1, const char *str2)
{
	(void) str2;
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(": insufficient arguments", 2);
}

void	too_many_args(const char *str1, const char *str2)
{
	(void) str2;
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(": too many arguments", 2);
}

void	exit_numeric_arg(const char *str1, const char *str2)
{
	(void) str2;
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

void	export_error(const char *str1, const char *str2)
{
	(void) str2;
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}
