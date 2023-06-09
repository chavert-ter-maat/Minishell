/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/02 11:57:54 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/05/23 14:51:23 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_split allocates with malloc and returns an array of strings 			  */
/* obtained by splitting ’s’ using the character ’c’ as a delimiter. 		  */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *string, char separator)
{
	int	count;

	count = 0;
	while (*string)
	{
		if (*string != separator)
		{
			while (*string != separator && *string)
				string++;
			count++;
		}
		else if (*string == separator && *string)
			string++;
	}
	return (count);
}

static int	free_split(char **split, int index)
{
	while (index-- > 0)
		free(split[index]);
	free(split);
	return (1);
}

static int	create_split(const char *string, char separator, char **split)
{
	size_t	start;
	size_t	end;
	int		index;

	start = 0;
	end = 0;
	index = 0;
	while (string[start])
	{
		if (string[start] != separator)
		{
			end = start;
			while (string[end] != separator && string[end])
				end++;
			split[index] = ft_substr(string, start, (end - start));
			if (!split[index])
				return (free_split(split, index));
			index++;
			start = end;
		}
		if (string[start] == separator && string[start])
			start++;
	}
	split[index] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	if (create_split(s, c, split) == 1)
		return (NULL);
	return (split);
}
