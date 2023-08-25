/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_non_builtin.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:16:04 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/25 14:41:13 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_path_executable(char **split_path, char **cmd)
{
	size_t	index;
	char	*tmp_path;
	char	*cmd_slash;

	if (split_path == NULL)
		return (cmd[0]);
	cmd_slash = ft_strjoin("/", cmd[0]);
	if (!cmd_slash)
		return (NULL);
	index = 0;
	while (split_path[index])
	{
		tmp_path = ft_strjoin(split_path[index], cmd_slash);
		if (!tmp_path)
			return (free(cmd_slash), NULL);
		if (access(tmp_path, F_OK | X_OK) == SUCCESS)
			break ;
		free(tmp_path);
		index++;
	}
	free(cmd_slash);
	if (split_path[index] == NULL)
		return (cmd[0]);
	return (tmp_path);
}

static char	**get_path_environment(t_shell *shell)
{
	char	*path;
	char	**split_path;

	path = env_get_var_value(shell, "PATH");
	if (!path)
		return (NULL);
	split_path = ft_split(path, ':');
	if (!split_path)
	{
		shell_error(shell, malloc_error, "get_path_environment", 1);
		_exit(1);
	}
	return (split_path);
}

void	execute_non_builtin(t_shell *shell, t_command *command)
{
	char	*command_path;
	char	**split_path;

	if (command->arg_list->count == 0)
		_exit(0);
	command_path = NULL;
	split_path = get_path_environment(shell);
	update_env(shell);
	if (command->args[0] && (ft_strncmp(command->args[0], "/", 1) 
			&& ft_strncmp(command->args[0], "./", 2)))
	{
		command_path = get_path_executable(split_path, command->args);
		if (!command_path)
		{
			shell_error(shell, print_error,
				"failed to get path to executable", 1);
			_exit(1);
		}
		if (execve(command_path, command->args, shell->envp) == FAILED)
			error_no_command(shell, command->args[0]);
	}
	else if (execve(command->args[0], command->args, shell->envp) == FAILED)
		error_perm_denied(shell, command->args[0]);
}
