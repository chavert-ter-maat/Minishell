/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/09 15:12:17 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/16 16:38:41 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*cs1;
	char	*cs2;
	size_t	i;

	cs1 = (char *) s1;
	cs2 = (char *) s2;
	i = 0;
	while (i < n)
	{
		if (cs1[i] != cs2[i])
			return ((unsigned char) cs1[i] - (unsigned char) cs2[i]);
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
	
	printf("%d\n", memcmp(s1, s2, 1));
	printf("%d\n", ft_memcmp(s1, s2, 1));
	return (0);
}
*/