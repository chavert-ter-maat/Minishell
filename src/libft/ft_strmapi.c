/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 17:02:31 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/14 17:20:29 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	char			*s2;
	unsigned int	i;

	len = ft_strlen(s);
	if (len == 0)
		return (ft_calloc(1, 1));
	s2 = malloc(len + 1);
	if (!s2)
		return (0);
	i = 0;
	while (i < len)
	{
		s2[i] = f(i, s[i]);
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
