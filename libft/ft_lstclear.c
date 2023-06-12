/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 12:11:27 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/05/23 09:45:08 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* Deletes and frees the given node and every successor of that node.		  */
/* ************************************************************************** */

#include "libft.h"

void ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *current;
	t_list *next;

	if (lst && *lst)
	{
		current = *lst;
		while (current)
		{
			next = current->next;
			if (del)
				del(current->content);
			free(current);
			current = next;
		}
		*lst = NULL;
	}
}
