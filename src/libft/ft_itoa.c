/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 15:57:11 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/10/16 16:23:51 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*ft_minvalue(void)
{
	char	*a;

	a = malloc(12);
	if (!a)
		return (0);
	ft_strlcpy(a, "-2147483648", 12);
	return (a);
}

static char	*ft_zero(void)
{
	char	*a;

	a = malloc(2);
	if (!a)
		return (0);
	a[0] = '0';
	a[1] = '\0';
	return (a);
}

static int	ft_findlen(int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		n = n / 10;
		len ++;
	}
	return (len);
}

static char	*ft_makestring(int n, int len, int neg)
{
	char	*a;

	a = malloc(len + 1 + neg);
	if (!a)
		return (0);
	a[len-- + neg] = '\0';
	if (neg == 1)
	{
		n *= -1;
		a[0] = '-';
	}
	while (len >= 0)
	{
		a[len-- + neg] = n % 10 + '0';
		n = n / 10;
	}
	return (a);
}

char	*ft_itoa(int n)
{
	int	len;
	int	neg;

	if (n == -2147483648)
		return (ft_minvalue());
	if (n == 0)
		return (ft_zero());
	neg = 0;
	if (n < 0)
		neg = 1;
	len = ft_findlen(n);
	return (ft_makestring(n, len, neg));
}
