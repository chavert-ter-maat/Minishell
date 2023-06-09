/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/02 09:53:48 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/01/13 10:02:51 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_itoa converts integer to string. Returns NULL if the allocation fails.  */
/* ************************************************************************** */

#include "libft.h"

static int	getlen(int number)
{
	int	lenght;

	lenght = 0;
	if (number == 0)
		return (1);
	if (number < 0)
		lenght++;
	while (number != 0)
	{
		number /= 10;
		lenght++;
	}
	return (lenght);
}

char	*ft_itoa(int n)
{
	int			lenght;
	long int	l_number;
	char		*string;

	l_number = (long int) n;
	lenght = getlen(l_number);
	string = ft_calloc((lenght + 1), sizeof(char));
	if (!string)
		return (NULL);
	if (l_number == 0)
		string[0] = '0';
	if (l_number < 0)
	{
		string[0] = '-';
		l_number *= -1;
	}
	while (l_number > 0)
	{
		string[lenght - 1] = (l_number % 10) + '0';
		l_number /= 10;
		lenght--;
	}
	return (string);
}
