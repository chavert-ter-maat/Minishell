/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   putpointer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 15:20:31 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/03/06 13:47:14 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	string_lenght(char *string)
{
	int	i;

	i = 0;
	if (!string)
		return (FAILED);
	while (string[i])
	{
		i++;
	}
	return (i);
}

static char	*ft_itoah(uintptr_t x)
{
	int		string_lenght;
	char	*string;
	char	*hex_string;	

	hex_string = "0123456789abcdef";
	string_lenght = get_lenght_hex(x);
	string = malloc((string_lenght + 3) * sizeof(char));
	if (!string)
		return (0);
	string[0] = '0';
	string[1] = 'x';
	string[string_lenght + 2] = '\0';
	while (string_lenght > 0)
	{
		string[string_lenght + 1] = hex_string[x % 16];
		x /= 16;
		string_lenght--;
	}
	return (string);
}

int	put_p(uintptr_t p)
{
	char	*string;
	int		lenght;

	string = ft_itoah(p);
	lenght = string_lenght(string);
	if (!string)
		return (FAILED);
	if (print_string(string) == FAILED)
		return (free(string), FAILED);
	free (string);
	return (lenght);
}
