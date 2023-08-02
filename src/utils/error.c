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

void env_error(const char *str)
{
    ft_putstr_fd("env: ", 2);
    ft_putstr_fd(str, 2);
    ft_putendl_fd(": No such file or directory", 2);
}

void	too_little_args(const char *str)
{
	ft_putstr_fd(str, 2);
    ft_putendl_fd(": insufficient arguments", 2);
}

void	too_many_args(const char *str)
{
	ft_putstr_fd(str, 2);
    ft_putendl_fd(": too many arguments", 2);
}

void	exit_numeric_arg(const char *str)
{
	ft_putstr_fd("exit: ", 2);
    ft_putstr_fd(str, 2);
    ft_putendl_fd(": numeric argument required", 2);
}

void	export_error(const char *str)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}