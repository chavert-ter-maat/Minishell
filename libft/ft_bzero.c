/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 15:13:35 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/01/13 09:42:07 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_bzero() function writes n zeroed bytes to the string s.				  */
/* If amount is zero, bzero() does nothing.									  */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t amount)
{
	char	*zeroed_string;
	size_t	index;

	zeroed_string = (char *)s;
	index = 0;
	while (index < amount)
	{
		zeroed_string[index] = '\0';
		index++;
	}
}
