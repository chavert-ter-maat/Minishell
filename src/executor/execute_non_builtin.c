#include "../../include/minishell.h"

// Checks if the executable can be found
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

// get_path() looks for the path in the environment
// where command executables can found
// !!unset PATH works, but doesnt give the same error message as bash for 100% 
static char	**get_path_environment(t_shell *shell)
{
	char	*path;
	char	**split_path;
	int		index;

	path = env_get_var_value(shell, "PATH");
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

// execute_non_builtin() finds path in environment, splits it and looks then looks if
// executable is present in the minishell directory, if not it looks for
// a path either in the environment or in the input.
void	execute_non_builtin(t_shell *shell, t_command *command)
{
	char	*command_path;
	char	**split_path;

	command_path = NULL;
	split_path = get_path_environment(shell);
	if (command->args[0] && (ft_strncmp(command->args[0], "/", 1) 
		|| ft_strncmp(command->args[0], "./", 2)))
	{
		command_path = get_path_executable(split_path, command->args);
		if (execve(command_path, command->args, shell->envp) == FAILED)
			error_no_command(shell, command->args[0]);
	}
	else if (execve(command->args[0], command->args, shell->envp) == FAILED)
		error_no_command(shell, command->args[0]);
}
