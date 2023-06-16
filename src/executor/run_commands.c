#include "../../include/minishell.h"

// find_path_to_executable looks if the executable can be found
// and if the there is permission to run the executable
static char	*get_path_executable(char **split_path, char **cmd)
{
	size_t	index;
	char	*tmp_path;
	char	*cmd_slash;

	if (split_path == NULL)
		return (cmd[0]);
	cmd_slash = ft_strjoin("/", cmd[0]);
	index = 0;
	while (split_path[index])
	{
		tmp_path = ft_strjoin(split_path[index], cmd_slash);
		if (access(tmp_path, F_OK | X_OK) == SUCCES)
			break ;
		free(tmp_path);
		index++;
	}
	free(cmd_slash);
	if (split_path[index] == NULL)
		return (cmd[0]);
	return (tmp_path);
}

// get_path() looks for the path in the environment
// where command executables can found

// !!unset PATH works, but doesnt give the same error message as bash for 100% 
static char	**get_path_environment(t_shell *shell)
{
	char	*path;
	char	**split_path;
	size_t	index;

	index = 0;
	while (shell->envp[index])
	{
		path = ft_strnstr(shell->envp[index], "PATH=", 5);
		if (path)
			break ;
		index++;
	}
	split_path = ft_split(&path[5], ':');
	if (!split_path)
		return(NULL);
	return (split_path);
}

// run_commands() finds path in environment, splits it and looks then looks if
// command is present in the folder or a path is given as a command.
// if not the path for the command is searched for
void	run_command(t_shell *shell, char *cmd)
{
	char	**splitted_cmd;
	char	*command_path;
	char	**split_path;

	command_path = NULL;
	split_path = get_path_environment(shell);
	splitted_cmd = ft_split(cmd, ' ');
	if (!splitted_cmd)
		error_exit("split splitted_cmd failed\n");
	if (splitted_cmd[0] && (ft_strncmp(splitted_cmd[0], "/", 1) 
		|| ft_strncmp(splitted_cmd[0], "./", 2)))
	{
		command_path = get_path_executable(split_path, splitted_cmd);
		if (execve(command_path, splitted_cmd, shell->envp) == FAILED)
			error_no_command(splitted_cmd[0]);
	}
	if (execve(splitted_cmd[0], splitted_cmd, shell->envp) == FAILED)
		error_no_command(splitted_cmd[0]);
}
