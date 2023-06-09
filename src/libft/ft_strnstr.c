/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/09 15:28:19 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/11 15:53:11 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (ft_strlen(needle) == 0)
		return ((char *) haystack);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (haystack[i] && haystack[i] != needle[j] && i < len)
			i++;
		while (haystack[i] && haystack[i] == needle[j] && (i < len))
		{
			i++;
			j++;
			if (needle[j] == '\0')
				return ((char *) &haystack[i - j]);
		}
		i -= j;
		if (haystack[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char haystack[50] = "aaaaabc";
	char needle[3] = "abc";
	printf("%s\n", strnstr(haystack, needle, 8));
	printf("%s\n", ft_strnstr(haystack, needle, 8));
	return (0);
}
*/