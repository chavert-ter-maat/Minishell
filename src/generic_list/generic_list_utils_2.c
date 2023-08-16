/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   generic_list_utils_2.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 14:59:09 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/16 15:34:51 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_node_data(t_func_ptr_free ft_free, void *data)
{
	if (ft_free)
		ft_free(data);
	else
		free(data);
}

t_list	*free_list(t_list *list)
{
	t_node	*temp;

	if (!list)
		return (NULL);
	temp = list->head;
	while (temp)
	{
		list->head = list->head->next;
		free_node_data(list->ft_free, temp->data);
		free(temp);
		temp = list->head;
	}
	free(list);
	return (NULL);
}

void	list_remove_head(t_list *list)
{
	t_node	*temp;

	if (!list || !list->head)
		return ;
	temp = list->head;
	list->head = list->head->next;
	if (!list->head)
		list->tail = NULL;
	free_node_data(list->ft_free, temp->data);
	free(temp);
	list->count--;
}

void	list_remove_index(t_list *list, int index)
{
	int		i;
	t_node	*current;
	t_node	*target;

	if (!list || index < 0 || index >= list->count)
		return ;
	if (index == 0)
		list_remove_head(list);
	else
	{
		i = 0;
		current = list->head;
		while (i < index -1)
		{
			current = current->next;
			i++;
		}
		target = current->next;
		current->next = target->next;
		if (!target->next)
			list->tail = current;
		free_node_data(list->ft_free, target->data);
		free(target);
		list->count--;
	}
}
