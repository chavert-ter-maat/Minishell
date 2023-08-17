/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/17 14:25:27 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/17 14:32:23 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_dir_up(char *oldpwd)
{
	int		str_len;
	char	*pwd;

	pwd = NULL;
	str_len = ft_strlen(oldpwd);
	while (oldpwd[--str_len])
	{
		if (oldpwd[str_len] == '/')
		{
			pwd = ft_strndup(oldpwd, str_len);
			break ;
		}
	}
	return (pwd);
}
