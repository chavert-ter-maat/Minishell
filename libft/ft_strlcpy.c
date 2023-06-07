/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 11:28:55 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/11 17:17:50 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = ft_strlen(src);
	if (len + 1 < dstsize)
		ft_memcpy(dst, src, len + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (len);
}
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char src1[14] = "Hello, world!";
	char dst1[14];
	char src2[14] = "Hello, world!";
	char dst2[14];
	
	printf("%lu\n", strlcpy(dst1, src1, 10));
	printf("%s\n", dst1);
	printf("%lu\n", ft_strlcpy(dst2, src2, 10));
	printf("%s\n", dst2);
	return (0);
}
*/