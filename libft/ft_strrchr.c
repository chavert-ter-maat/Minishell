/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 17:06:50 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/01/13 10:43:10 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_strrchr() locates the last occurrence of c in string pointed to by s.	  */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	lenght;
	char	*string;

	string = (char *)s;
	lenght = ft_strlen(string);
	while (string[lenght] != (char)c)
	{
		if (lenght == 0)
			return (NULL);
		lenght--;
	}
	return (&string[lenght]);
}
