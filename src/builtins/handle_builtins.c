#include "../../include/minishell.h"

int execute_builtin(t_shell *shell)
{
	if (ft_strncmp(shell->command->args[0], "cd", 3) == 0)
	 return (ft_cd(shell, shell->command));
	if (ft_strncmp(shell->command->args[0], "echo", 5) == 0)
		return (ft_echo(shell->command->args, 1));
	if (ft_strncmp(shell->command->args[0], "env", 4) == 0)
		return (ft_env(shell));
	if (ft_strncmp(shell->command->args[0], "export", 7) == 0)
	 return (ft_export(shell->command, &shell->env_list));
	if (ft_strncmp(shell->command->args[0], "pwd", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(shell->command->args[0], "unset", 6) == 0)
	 return (ft_unset(shell->command, &shell->env_list));
	if (ft_strncmp(shell->command->args[0], "exit", 5) == 0)
	 return (TRUE);
	return (SUCCESS);
}
int check_if_builtin(char *command)
{
	if (ft_strncmp(command, "cd", 3) == 0)
		return (TRUE);
	if (ft_strncmp(command, "echo", 5) == 0)
		return (TRUE);
	if (ft_strncmp(command, "env", 4) == 0)
		return (TRUE);
	if (ft_strncmp(command, "export", 7) == 0)
		return (TRUE);
	if (ft_strncmp(command, "pwd", 4) == 0)
		return (TRUE);
	if (ft_strncmp(command, "unset", 6) == 0)
		return (TRUE);
	if (ft_strncmp(command, "exit", 5) == 0)
		return (TRUE);
	return (FALSE);
}