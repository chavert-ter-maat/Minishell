/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 15:05:02 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/01/13 10:18:23 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_strchr() locates the first occurrence of c in string pointed to by s.   */
/* ft_strchr() return a pointer to the located character,					  */
/* or NULL if the character does not appear in the string.					  */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*string;
	size_t	index;

	string = (char *)s;
	index = 0;
	while (string[index] != (char)c)
	{
		if (string[index] == '\0')
			return (NULL);
		index++;
	}	
	return (&string[index]);
}
