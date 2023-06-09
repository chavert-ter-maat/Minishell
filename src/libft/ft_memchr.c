/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 16:00:42 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/16 16:36:24 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cs;
	size_t			i;

	cs = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (cs[i] == (unsigned char) c)
			return (&cs[i]);
		i++;
	}
	return (0);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char s1[14] = "Hello, world!";
	char s2[14] = "Hello, world!";

	printf("%s\n", memchr(s1, 'o', 14));
	printf("%s\n", ft_memchr(s2, 'o', 14));
	return (0);
}
*/