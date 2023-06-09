/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 17:42:18 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/04/30 14:08:53 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_strnstr() function locates the first occurrence of					  */
/* the null-terminated string needle in the string haystack,				  */
/* where not more than len characters are searched.							  */
/* If needle is an empty string, haystack is returned; if needle			  */
/* occurs nowhere in haystack, NULL is returned; otherwise a pointer to the	  */
/* first character of the first occurrence of needle is returned.			  */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	index1;
	size_t	index2;
	size_t	lenght_needle;

	index1 = 0;
	index2 = 0;
	lenght_needle = ft_strlen(needle);
	if (lenght_needle == 0)
		return ((char *)haystack);
	while (haystack[index1] && index1 < len)
	{
		index2 = 0;
		while (haystack[index1 + index2] == needle[index2]
			&& haystack[index1 + index2]
			&& needle[index2] && index1 + index2 < len)
		{		
			index2++;
			if (lenght_needle == index2)
				return ((char *)&haystack[index1]);
		}
		index1++;
	}
	return (0);
}
