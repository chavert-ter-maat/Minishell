/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 12:23:08 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/12 17:35:57 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char const	*ft_findstart(char const *s1, char const *set)
{
	int		iset;

	while (*s1)
	{
		iset = 0;
		while (set[iset])
		{
			if (*s1 == set[iset])
			{
				s1 ++;
				iset = 0;
			}
			else
			{
				iset ++;
				if (!set[iset])
					return (s1);
			}
		}
	}
	return (0);
}

static char const	*ft_findend(char const *s1, char const *set)
{
	int			iset;
	const char	*starts1;

	starts1 = s1;
	s1 += ft_strlen(s1) -1;
	while (*s1 && s1 > starts1)
	{
		iset = 0;
		while (set[iset] && s1 > starts1)
		{
			if (*s1 == set[iset])
			{
				s1 --;
				iset = 0;
			}
			else
			{
				iset ++;
				if (!set[iset])
					return (s1);
			}
		}
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*start;
	char const	*end;
	char		*s2;

	if (ft_strlen(set) == 0)
		return (ft_strdup(s1));
	if (ft_strlen(s1) == 0)
		return (ft_calloc(1, 1));
	start = ft_findstart(s1, set);
	end = ft_findend(s1, set);
	if (end - start < 0)
		return (ft_calloc(1, 1));
	s2 = malloc(end - start + 2);
	if (!s2)
		return (0);
	s2 = ft_memcpy(s2, start, end - start + 1);
	s2[end - start + 1] = '\0';
	return (s2);
}
/*
#include <stdio.h>
int	main(void)
{
	char s1[] = "*!*He!!o!*!";
	char set[] = "";
	char *s2;

	s2 = ft_strtrim(s1, set);
	printf("%s\n", s2);
	free (s2);
	return (0);
}
*/