/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:26:08 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/11 18:30:27 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s2;

	len = ft_strlen(s1);
	s2 = malloc(len + 1);
	if (!s2)
		return (0);
	ft_strlcpy(s2, s1, len + 1);
	return (s2);
}
/*
#include <stdio.h>
int	main(void)
{
	char	s1[14] = "Hello, world!";
	char	*s2;

	s2 = ft_strdup(s1);
	printf("%s\n", s2);
	free(s2);
	return (0);
}
*/