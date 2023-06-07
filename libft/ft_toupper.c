/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 14:41:41 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/08 14:50:48 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= ('a' - 'A');
	return (c);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	char c1 = 'b';
	char c2 = 'b';

	printf("%c\n", toupper(c1));
	printf("%c\n", ft_toupper(c2));
	return (0);
}
*/