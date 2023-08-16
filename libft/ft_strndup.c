/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:28:23 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/16 15:28:24 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	size_t	i;
	char	*dup;

	if (!str)
		return (NULL);
	if (ft_strlen(str) < n)
		n = ft_strlen(str);
	dup = ft_calloc (n + 1, sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = str[i];
		i++;
	}
	dup[n] = '\0';
	return (dup);
}
