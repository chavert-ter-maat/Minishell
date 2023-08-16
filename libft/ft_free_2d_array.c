/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_2d_array.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 09:39:05 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/08/16 15:32:16 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ************************************************************************** */
/* ft_free_2d_array(char ***cmd) frees a two dimentional array				  */
/* ************************************************************************** */

void	ft_free_2d_array(char ***array)
{
	int	index;

	index = 0;
	if (!*array)
		return ;
	while ((*array)[index])
	{
		free((*array)[index]);
		index++;
	}
	free(*array);
	*array = NULL;
}
