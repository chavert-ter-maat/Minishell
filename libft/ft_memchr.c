/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 18:24:51 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/02/01 15:36:01 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_memchr locates the first occurrence of 								  */
/* c (converted to an unsigned char) in string.								  */
/* ft_memchr returns a pointer to the byte located, 						  */
/* or NULL if no such byte exists within n amount bytes.					  */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*string;
	unsigned char	character;
	size_t			index;

	string = (unsigned char *)str;
	character = (unsigned char)c;
	index = 0;
	while (index < n)
	{
		if (string[index] == character)
			return ((void *)&string[index]);
		index++;
	}
	return (NULL);
}
