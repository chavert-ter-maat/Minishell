/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: chaverttermaat <chaverttermaat@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 13:58:06 by chavertterm   #+#    #+#                 */
/*   Updated: 2023/05/02 12:28:39 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format(va_list argument_list, const char format)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += put_c(va_arg(argument_list, int));
	if (format == 'd' || format == 'i')
		count += put_id(va_arg(argument_list, int));
	if (format == 's')
		count += put_s(va_arg(argument_list, char *));
	if (format == 'u')
		count += put_u(va_arg(argument_list, unsigned int));
	if (format == 'x' || format == 'X')
		count += put_x(va_arg(argument_list, unsigned int), format);
	if (format == 'p')
		count += put_p(va_arg(argument_list, uintptr_t));
	if (format == '%')
		count += put_perc();
	return (count);
}

int	ft_printf(const char *string, ...)
{	
	int		index;
	int		count;
	int		protect;
	va_list	argument_list;

	index = 0;
	count = 0;
	va_start(argument_list, string);
	while (string[index])
	{	
		if (string[index] == '%' && string[index + 1] != '\0')
		{
			protect = format(argument_list, string[index + 1]);
			index++;
		}
		else
			protect = put_c(string[index]);
		if (protect == FAILED)
			return (FAILED);
		count += protect;
		index++;
	}
	va_end(argument_list);
	return (count);
}
