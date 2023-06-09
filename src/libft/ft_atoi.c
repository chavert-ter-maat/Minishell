/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 17:47:15 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/01/13 10:03:32 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* The atoi() function converts the initial portion of the string 			  */
/* pointed to by str to int representation. 								  */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	index;
	int	result;
	int	sign;

	index = 0;
	sign = 1;
	result = 0;
	while ((str[index] >= 9 && str[index] <= 13) || (str[index] == 32))
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			(sign *= -1);
		index++;
	}
	while ((str[index] >= '0' && str[index] <= '9') && str[index])
	{
		result = result * 10;
		result = (result + (str[index] - '0'));
		index++;
	}
	return (sign * result);
}
