/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 15:13:35 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/01/11 17:31:10 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_calloc() contiguously allocates enough space for count objects that are */
/* size bytes of memory each and returns a pointer to the allocated memory.	  */
/* The allocated memory is filled with bytes of value zero.					  */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*memory;

	memory = malloc(count * size);
	if (memory == NULL)
		return (NULL);
	ft_bzero(memory, (count * size));
	return (memory);
}
