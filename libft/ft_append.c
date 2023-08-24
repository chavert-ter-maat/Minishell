/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_append.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 18:12:27 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/24 17:41:53 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* like strcat() but the string str1 does not need to have
sufficient space to hold the result */

#include "libft.h"

char	*ft_append(char *str1, char *str2)
{
	char	*append;
	size_t	size;

	if (!str2)
		return (str1);
	if (!str1)
		return (str2);
	size = ft_strlen(str1) + ft_strlen(str2) + 1;
	append = ft_calloc(size, sizeof(char));
	if (!append)
		return (free(str1), NULL);
	append[0] = '\0';
	ft_strlcat(append, str1, size);
	ft_strlcat(append, str2, size);
	return (free(str1), append);
}
