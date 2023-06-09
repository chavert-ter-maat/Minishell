/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 17:42:18 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/05/25 11:02:01 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_strncmp() function compares not more than n characters of s1 and s2.    */
/* ft_strncmp() function return an integer greater than,					  */
/* equal to, or less than 0, according as the string 						  */
/* s1 is greater than, equal to, or less than the string s2.				  */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	if (n == 0)
		return (0);
	while (s1[index] == s2[index] && index < n - 1)
			index++;
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}
