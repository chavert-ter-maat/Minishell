/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 14:53:42 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/10 14:06:12 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += ('a' - 'A');
	return (c);
}
/*
#include <ctype.h>
#include <stdio.h>
int	main(void)
{
	char c1 = 'A';
	char c2 = 'A';
	
	printf("%c\n", tolower(c1));
	printf("%c\n", ft_tolower(c2));
	return (0);
}
*/