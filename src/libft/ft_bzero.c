/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 12:17:48 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/11 12:49:07 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	ft_bzero(void *src, size_t n)
{
	ft_memset(src, 0, n);
}
/*
#include <strings.h>
#include <stdio.h>
int	main(void)
{
	char str1[14] = "Hello, world!";
	char str2[14] = "Hello, world!";

	bzero(str1 + 4, 3);
	printf("%s\n", str1);
	printf("%s\n", str1 + 7);
	ft_bzero(str2 + 4, 3);
	printf("%s\n", str2);
	printf("%s\n", str2 + 7);
	return(0);
}
*/