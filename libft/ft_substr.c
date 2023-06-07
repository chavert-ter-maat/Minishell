/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:07:30 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/12 10:56:15 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (start >= ft_strlen(s) || ft_strlen(s) == 0)
		len = 0;
	if (len != 0 && ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub = malloc(len + 1);
	if (!sub)
		return (0);
	sub = ft_memcpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}
/*
#include <stdio.h>
int	main(void)
{
	const char s1[14] = "Hello, world!";
	char *sub;

	sub = ft_substr(s1, 7, 6);
	printf("%s\n", sub);
	free(sub);
	return (0);
}
*/