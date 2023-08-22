/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:18:18 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/22 13:31:01 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_n_flag(char *str)
{
	int	index;
	int	str_length;

	index = 2;
	str_length = ft_strlen(str);
	if (!str)
		return (NOT_FOUND);
	if (ft_strncmp(str, "-n", 2) == 0)
	{
		while (index < str_length)
		{
			if (ft_strncmp(&str[index], "n", 1) != 0)
				return (NOT_FOUND);
			index++;
		}
		return (FOUND);
	}
	else
		return (NOT_FOUND);
}

void	ft_echo(t_shell *shell, char **args, int fd)
{
	int	n_flag;
	int	index;

	n_flag = 0;
	index = 1;
	while (check_n_flag(args[index]) == FOUND)
	{
		n_flag = FOUND;
		index++;
	}
	while (args[index])
	{
		if (args[index])
			ft_putstr_fd(args[index], fd);
		if (args[index + fd])
			ft_putchar_fd(' ', fd);
		index++;
	}
	if (n_flag == NOT_FOUND)
		ft_putchar_fd('\n', fd);
	shell->status = 0;
}
