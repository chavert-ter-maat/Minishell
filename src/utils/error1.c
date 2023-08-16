/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error1.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 14:49:16 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/16 15:49:38 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	shell_error(t_shell *shell, void (*func)(const char *),
		const char *str1, int ret)
{
	g_status = ret;
	ft_putstr_fd("shellyeah: ", 2);
	func(str1);
	free_shell(shell);
}

void	syntax_error(const char *str1)
{
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd("'", 2);
}

void	print_error(const char *str1)
{
	ft_putendl_fd(str1, 2);
}

void	malloc_error(const char *str1)
{
	ft_putstr_fd("Memory allocation failed in ", 2);
	ft_putendl_fd(str1, 2);
}

void	dir_error(const char *str1)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(": No such file or directory", 2);
}
