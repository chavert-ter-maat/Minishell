/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 17:47:15 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/01/13 10:35:37 by cter-maa      ########   odam.nl         */
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
	string = malloc(sizeof(char) * ft_strlen(s) + 1);
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
