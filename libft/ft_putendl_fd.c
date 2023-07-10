/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 17:47:15 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/06/22 17:28:26 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* Outputs the string ’s’ to the given file descriptor followed by a newline. */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(const char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
