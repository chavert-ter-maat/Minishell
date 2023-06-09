/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: chaverttermaat <chaverttermaat@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 12:31:46 by chavertterm   #+#    #+#                 */
/*   Updated: 2023/05/02 12:22:15 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// HEADERS
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdint.h>

// DEFINES
# define FAILED -1

// FUNCTIONS
int	ft_printf(const char *string, ...);
int	get_lenght(int number);
int	get_lenght_hex(unsigned int number);
int	print_string(char *string);
int	put_perc(void);
int	put_c(int character);
int	put_id(int number);
int	put_p(uintptr_t pointer);
int	put_s(char *string);
int	put_u(unsigned int u);
int	put_x(unsigned int x, const char format);

#endif