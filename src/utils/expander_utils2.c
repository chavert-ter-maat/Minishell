/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 15:15:43 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/24 17:48:45 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	list_add_exp_quote(t_shell *shell, t_list *list, char *str)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (free(str), shell_error(shell, malloc_error, "expand_quote", 1));
	new->str = str;
	new->type = WORD;
	if (list_add_new_node(shell, list, new))
		free(new);
	else
		free_token(new);
}
