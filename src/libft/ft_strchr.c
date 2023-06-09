/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 14:58:59 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/12 10:02:56 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = c;
	while (*s != ch)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	return ((char *) s);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char str1[] = "tbfdlsf";
	char str2[] = "tbfdlsf";
	
	printf("%s\n", strchr(str1, 't' + 256));
	printf("%s\n", ft_strchr(str2, 't' + 256));
	return (0);
}
*/