#include "../../include/minishell.h"

t_list	*list_create(t_shell *shell, size_t data_size, func_ptr_free ft_free, func_ptr_comp ft_comp)
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

void	list_add_new_node(t_shell *shell, t_list *list, void *data)
{
	t_node	*new;

	if (!shell || !list || !data)
		return ;
	new = list_new_node(shell, list, data);
	list_add_node(list, new);
}

void	list_remove_head(t_list *list)
{
	t_node	*temp;

	if (!list || !list->head)
		return;
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
	int 	i;
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
		while(i < index -1)
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
			printf("CHECK found node\n");
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
