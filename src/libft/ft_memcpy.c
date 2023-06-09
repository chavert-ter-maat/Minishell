/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 11:16:02 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/01/11 17:24:37 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_memcpy() function copies n bytes from memory src to memory area dst     */
/* If dst and src overlap, behavior is undefined.							  */
/* ft_memcpy() function returns the original value of dst.					  */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	index;
	char	*destination;
	char	*source;

	destination = (char *)dst;
	source = (char *)src;
	index = 0;
	if (destination == 0 && source == 0 && n > 0)
		return (0);
	while (index < n)
	{
		destination[index] = source[index];
		index++;
	}
	return (dst);
}
