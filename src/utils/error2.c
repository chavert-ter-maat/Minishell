/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 14:57:36 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/16 14:57:40 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	dir_unset(const char *str1)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(" not set", 2);
}

void	too_little_args(const char *str1)
{
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(": insufficient arguments", 2);
}

void	too_many_args(const char *str1)
{
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(": too many arguments", 2);
}

void	exit_numeric_arg(const char *str1)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

void	export_error(const char *str1)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}
