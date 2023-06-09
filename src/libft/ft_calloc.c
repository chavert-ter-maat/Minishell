/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:09:03 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/11 18:27:58 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*re;

	re = (malloc(count * size));
	if (!re)
		return (0);
	ft_bzero(re, count * size);
	return (re);
}
/*
int	main(void)
{
	char *s;

	s = ft_calloc(4, 3);
	free(s);
	return (0);
}
*/