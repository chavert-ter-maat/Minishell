/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtolower.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 15:11:45 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/06/28 15:17:29 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtolower(char *str)
{
	size_t	i;
	size_t	len;

	len = ft_strlen((const char *) str);
	i = 0;
	while (i < len)
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}
