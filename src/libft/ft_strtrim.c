/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 17:06:50 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/01/13 10:47:07 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_strtrim returns a copy of ’s1’ with the characters specified 			  */
/*  in ’set’ removed from the beginning and the end of string.				  */
/* ************************************************************************** */

#include "libft.h"

static int	getset(char const *set, const char c)
{
	size_t	index;

	index = 0;
	while (set[index])
	{
		if (set[index] == c)
			return (1);
		index++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	end;
	unsigned int	start;
	char			*trimmed_string;

	end = ft_strlen(s1);
	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && getset(set, s1[start]))
		start++;
	while (end > start && getset(set, s1[end - 1]))
		end--;
	trimmed_string = ft_substr(s1, start, (end - start));
	return (trimmed_string);
}
