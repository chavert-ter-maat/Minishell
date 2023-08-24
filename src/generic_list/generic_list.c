/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   generic_list.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 14:59:53 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/24 17:47:33 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*list_create(t_shell *shell, size_t data_size, t_func_ptr_free ft_free,
		t_func_ptr_comp ft_comp)
{
	t_list	*list;

	list = ft_calloc(1, sizeof(t_list));
	if (!list)
		return (shell_error(shell, malloc_error, "list_create()", 1), NULL);
	list->data_size = data_size;
	list->ft_free = ft_free;
	list->ft_comp = ft_comp;
	return (list);
}

static t_node	*list_new_node(t_shell *shell, t_list *list, void *data)
{
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	if (!new)
		return (shell_error(shell, malloc_error, "list_new_node()", 1), NULL);
	new->data = ft_calloc(1, list->data_size);
	if (!new->data)
	{
		free(new);
		return (shell_error(shell, malloc_error, "list_new_ode()", 1), NULL);
	}
	ft_memcpy(new->data, data, list->data_size);
	return (new);
}

static void	list_add_node(t_list *list, t_node *node)
{
	if (!node)
		return ;
	if (!list->head)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
	list->count++;
}

int	list_add_new_node(t_shell *shell, t_list *list, void *data)
{
	t_node	*new;

	if (!shell || !list || !data)
		return (0);
	new = list_new_node(shell, list, data);
	if (!new)
		return (0);
	list_add_node(list, new);
	return (1);
}
