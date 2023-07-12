/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/01 15:37:56 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/06/23 10:16:05 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* ft_lstnew() allocates with ft_calloc and returns a new node.				  */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = ft_calloc(1, sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

// int	main(void)
// {
// 	char	str[] = "banaan";
// 	t_list	*ptr;
// 	t_list	*new_ptr;

// 	ptr = ft_lstnew((void *)str);
// 	//printf("\n%s\n", ptr->content);
// 	new_ptr = ptr;
// 	printf("%s\n", new_ptr->content);
// 	return 0;
// }
