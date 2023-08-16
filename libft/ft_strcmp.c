/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 13:07:46 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/16 15:29:34 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	len;

	if (!s1 || !s2)
		return (1);
	len = ft_strlen(s1);
	if (ft_strlen(s2) < len)
		len = ft_strlen(s2);
	i = 0;
	while (s1[i] == s2[i] && i < len)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
