/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 14:50:53 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/16 16:55:55 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	**ft_returnoriginalstring(const char *s)
{
	char	**re;

	re = malloc(2 * sizeof(char *));
	if (!re)
		return (0);
	re[0] = ft_strdup(s);
	if (!re[0])
	{
		free(re);
		return (0);
	}
	re[1] = 0;
	return (re);
}

static char	**ft_returnnullpointer(void)
{
	char	**re;

	re = malloc(sizeof(char *));
	if (!re)
		return (0);
	re[0] = 0;
	return (re);
}

static char	**ft_makeparts(char **split, const char *s, char c, int parts)
{
	int	i;
	int	len;

	i = 0;
	while (i < parts)
	{
		while (*s && *s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		split[i] = malloc(len + 1);
		if (!split[i])
		{
			while (i-- > 0)
				free(split[i]);
			free(split);
			return (0);
		}
		ft_memcpy(split[i], s, len);
		split[i][len] = '\0';
		s += len;
		i++;
	}
	return (split);
}

static int	ft_countparts(const char *s, char c)
{
	int	parts;

	parts = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			parts++;
		while (*s && *s != c)
			s++;
	}
	return (parts);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		parts;

	if (!ft_strlen(s))
		return (ft_returnnullpointer());
	if (!c)
		return (ft_returnoriginalstring(s));
	parts = ft_countparts(s, c);
	if (parts == 0)
		return (ft_returnnullpointer());
	split = malloc((parts + 1) * sizeof(char *));
	if (!split)
		return (0);
	split = ft_makeparts(split, s, c, parts);
	split[parts] = 0;
	return (split);
}
/*
#include <stdio.h>
int	main(void)
{
	char str[] = "";
	char c = ' ';
	char	**split;
	
	split = ft_split(str, c);
	printf("%s\n, split[0]);
	free(split[0]);
	free(split);
	return (0);
	
}
*/