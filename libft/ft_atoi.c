/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 10:30:22 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/16 16:15:34 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;
	int	x;

	i = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	x = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		x *= 10;
		x += (str[i] - '0');
		i++;
	}
	x *= neg;
	return (x);
}
/*
#include <stdlib.h>
#include <stdio.h>
int	main(void)
{
	const char str[100] = "\n\n  \t \f \v+00014356a83";

	printf("%d\n", atoi(str));
	printf("%d\n", ft_atoi(str));
	return (0);
}
*/