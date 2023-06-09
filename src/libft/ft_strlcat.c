/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:14:23 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/16 17:21:22 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstsize < dstlen)
		dstlen = dstsize;
	if (dstsize == dstlen)
		return (dstlen + srclen);
	if (srclen < dstsize - dstlen)
		ft_memcpy(dst + dstlen, src, srclen + 1);
	else
	{
		ft_memcpy(dst + dstlen, src, dstsize - dstlen - 1);
		dst[dstsize - 1] = '\0';
	}
	return (dstlen + srclen);
}
/*
//if the dstsize is (incorrectly) smaller then the original dst, the return
//value behaves differently then the manual describes
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char dst1[20] = "pqrstuvwxyz";
	char src1[20] = ", world!";
	char dst2[20] = "Hello";
	char src2[20] = ", world!";

	printf("%lu\n", strlcat(dst1, src1, 9));
	printf("%s\n", dst1);
	printf("%lu\n", ft_strlcat(dst2, src2, 9));
	printf("%s\n", dst2);
	return (0);
}
*/