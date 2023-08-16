/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 17:47:15 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/08/16 15:29:00 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_strjoin allocates with ft_calloc and returns a new string,		 	  */
/* which is the result of the concatenation of ’s1’ and ’s2’.				  */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	index1;
	size_t	index2;
	size_t	lenght;
	char	*new_string;

	lenght = ft_strlen(s1) + ft_strlen(s2);
	new_string = ft_calloc(lenght + 1, sizeof(char));
	if (!new_string)
		return (NULL);
	index1 = 0;
	while (s1[index1])
	{
		new_string[index1] = s1[index1];
		index1++;
	}
	index2 = 0;
	while (s2[index2])
	{
		new_string[index1 + index2] = s2[index2];
		index2++;
	}
	new_string[index1 + index2] = '\0';
	return (new_string);
}
