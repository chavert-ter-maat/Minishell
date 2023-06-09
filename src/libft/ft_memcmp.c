/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 18:24:51 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/01/11 17:26:55 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_memcmp() compares byte string s1 against byte string s2.	    		  */
/* Both strings are assumed to be n bytes long.								  */
/* ft_memcmp() returns zero if the two strings are identical,				  */
/* otherwise returns the difference between the first two differing bytes	  */
/* Zero-length strings are always identical.  								  */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*string1;
	unsigned char	*string2;
	size_t			index;

	string1 = (unsigned char *)s1;
	string2 = (unsigned char *)s2;
	index = 0;
	while (index < n)
	{
		if (string1[index] != string2[index])
			return (string1[index] - string2[index]);
		index++;
	}
	return (0);
}
