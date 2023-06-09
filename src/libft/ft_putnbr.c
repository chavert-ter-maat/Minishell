/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 10:02:55 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/06/05 10:03:18 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void putnbr(int nb)
{
	char c;
	
	if (nb == INT_MIN)
	{
		write(1, "-2147483648", 11);
		return;
	}
	else if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
	}	
	if (nb > 9)
		putnbr(nb /10);
	c = (nb % 10) + '0';
	write(1, &c, 1);

}
