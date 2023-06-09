/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 18:02:16 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/16 17:19:08 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*re;

	len = ft_strlen(s1) + ft_strlen(s2);
	re = malloc(len + 1);
	if (!re)
		return (0);
	ft_strlcpy(re, s1, len + 1);
	ft_strlcat(re, s2, len + 1);
	return (re);
}
/*
#include <stdio.h>
int	main(void)
{
	char	s1[] = "Hello, ";
	char	s2[] = "world!";
	char	*s3;

	s3 = ft_strjoin(s1, s2);
	printf("%s\n", s3);
	free(s3);
	return (0);
}
*/