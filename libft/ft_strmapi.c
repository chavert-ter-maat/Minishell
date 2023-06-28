/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 17:47:15 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/06/23 10:17:18 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_strmapi applies the function ’f’ to each character of the string ’s’,	  */
/* and passing its index as first argument to create a new string			  */
/* resulting from successive applications of ’f’.							  */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*string;

	if (!s || !f)
		return (NULL);
	string = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (string == NULL)
		return (NULL);
	index = 0;
	while (s[index])
	{
		string[index] = f(index, s[index]);
		index++;
	}
	string[index] = '\0';
	return (string);
}
