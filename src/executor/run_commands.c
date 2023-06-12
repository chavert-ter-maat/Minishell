#include "../../include/minishell.h"

// find_path_to_executable looks if the executable can be found
// and if the there is permission to run the executable
static char	*find_path_to_executable(char **split_path, char **cmd)
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

// !!check for no path in environment!!
static char	**get_path_from_environment(t_shell *shell)
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
void	run_commands(t_shell *shell)
{
	char	**cmds;
	char	*cmd_path;
	char	**split_path;

	cmd_path = NULL;
	split_path = get_path_from_environment(shell);
	cmds = ft_split(shell->argv[2], ' ');
	if (!cmds)
		error_exit("split cmds failed\n");
	if (cmds[0] && (ft_strncmp(cmds[0], "/", 1) 
		|| ft_strncmp(cmds[0], "./", 2)))
	{
		cmd_path = find_path_to_executable(split_path, cmds);
		if (execve(cmd_path, cmds, shell->envp) == FAILED)
			error_no_command(cmds[0]);
	}
	if (execve(cmds[0], cmds, shell->envp) == FAILED)
		error_no_command(cmds[0]);
}
