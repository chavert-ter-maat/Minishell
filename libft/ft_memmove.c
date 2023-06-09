/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 13:39:02 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/01/13 10:04:59 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_memmove() copies len bytes from string src to string dst.	 			  */
/* The two strings may overlap; the copy is									  */
/* always done in a non-destructive manner.									  */
/* ft_memmove() returns the original value of dst.							  */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*destination;
	char	*source;
	size_t	index;

	index = 0;
	destination = (char *)dst;
	source = (char *)src;
	if (destination == 0 && source == 0 && len > 0)
		return (0);
	if (destination > source)
	{
		while (len > 0)
		{
			len--;
			destination[len] = source[len];
		}
	}
	while (index < len)
	{
		destination[index] = source[index];
		index++;
	}
	return (dst);
}
