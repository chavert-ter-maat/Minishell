/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:50:29 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/01/13 10:25:34 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_strlcat() appends string src to the end of dst.  It will append at most */
/* dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate,		  */
/* unless dstsize is 0 or the original dst string was longer than			  */
/* dstsize. If the src and dst strings overlap, the behavior is undefined.	  */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	index;
	size_t	len_dst;
	size_t	len_src;
	char	*string;

	string = (char *)src;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	index = 0;
	if (dstsize < len_dst + 1)
		return (dstsize + len_src);
	if (dstsize - 1 > len_dst)
	{
		while (dstsize - 1 > (index + len_dst) && string[index])
		{
			dst[len_dst + index] = string[index];
			index++;
		}
		dst[len_dst + index] = '\0';
	}
	return (len_dst + len_src);
}
