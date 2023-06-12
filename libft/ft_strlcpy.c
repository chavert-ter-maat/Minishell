/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:50:29 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/01/13 10:55:47 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_strlcpy() takes the full size of the 									  */
/* destination buffer and guarantee NUL-termination if there is room.		  */
/* ft_strlcpy() copies up to dstsize - 1 characters from the string src 	  */
/* to dst, NULL-terminating the result if dstsize is not 0.					  */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	index;

	index = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize > 0)
	{
		while ((dstsize - 1) > index && src[index])
		{
			dst[index] = src[index];
			index++;
		}
	}
	dst[index] = '\0';
	return (ft_strlen(src));
}
