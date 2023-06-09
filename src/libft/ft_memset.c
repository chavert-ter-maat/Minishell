/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 20:05:01 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/11 16:51:24 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *dst, int c, size_t len)
{
	unsigned char	*i;

	i = dst;
	while (len > 0)
	{
		*i++ = c;
		len --;
	}
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char str1[] = "Hello";
	char str2[] = "Hello";

	memset(str1, '!', 8);
	printf("%s\n", str1);
	ft_memset(str2, '!', 8);
	printf("%s\n", str2);
	return (0);
}
*/