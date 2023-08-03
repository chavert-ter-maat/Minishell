#include "../../include/minishell.h"

int	list_get_index(t_list *list, void *data)
{
	int		i;
	t_node	*current;

	if (!list || !data || !list->ft_comp)
		return (-1);
	i = 0;
	current = list->head;
	while (current)
	{
		if (list->ft_comp(current->data, data) == 0)
			return (i);
		current = current->next;
		i++;
	}
	return (-1);
}

void	list_remove_node(t_list *list, void *data)
{
	t_node	*previous;
	t_node	*target;

	if (!list || !list->head || !data)
		return ;
	target = list->head;
	if (list->ft_comp(target->data, data) == 0)
		return (list_remove_head(list));
	while (target->next)
	{
		previous = target;
		target = target->next;
		if (list->ft_comp(target->data, data) == 0)
		{
			previous->next = target->next;
			if (!target->next)
				list->tail = previous;
			free_node_data(list->ft_free, target->data);
			free(target);
			list->count--;
			return ;
		}
	}
}

bool	list_contains(t_list *list, void *data)
{
	t_node	*temp;

	if (!list || !data)
		return (NULL);
	temp = list->head;
	while (temp)
	{
		if (list->ft_comp(temp->data, data) != 0)
			return (true);
		temp = temp->next;
	}
	return (false);
}

bool	list_is_identical(t_list *list1, t_list *list2)
{
	t_node	*temp;

	if (!list1 || !list2)
		return (false);
	if (list1->count != list2->count)
		return (false);
	temp = list1->head;
	while (temp)
	{
		if (list_contains(list2, temp->data) == false)
			return (false);
		temp = temp->next;
	}
	return (true);
}

t_node	*list_get_node(t_list *list, void *data)
{
	t_node	*current;

	if (!list || !data || !list->ft_comp)
		return (NULL);
	current = list->head;
	while (current)
	{
		if (list->ft_comp(current->data, data) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
