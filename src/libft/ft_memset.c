/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 13:55:27 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/01/13 10:08:44 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_memset writes len bytes of value c to the string b.					  */
/* ft_memset returns its first argument.									  */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*string;
	size_t			index;

	index = 0;
	string = (unsigned char *)b;
	while (index < len)
	{
		string[index] = (unsigned char)c;
		index++;
	}
	return (b);
}
