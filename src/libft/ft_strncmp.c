/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 15:34:22 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/16 17:32:56 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < n)
	{
		if (s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	if (n == i)
		return (0);
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char *big = "abcdef";
 	char *little = "abcdefghijklmnop";
 	size_t size = 6;
	ft_strncmp(big, little, size);
	return (0);
}
*/