/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 15:05:02 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/08/16 15:29:15 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_strdup allocates sufficient memory for a copy of the string s1,		  */
/* and returns a pointer to it.												  */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	index;
	char	*new_string;

	if (!s1)
		return (NULL);
	index = 0;
	new_string = ft_calloc (ft_strlen(s1) + 1, sizeof(char));
	if (!new_string)
		return (NULL);
	while (s1[index])
	{
		new_string[index] = s1[index];
		index++;
	}
	new_string[index] = '\0';
	return (new_string);
	free (new_string);
}
