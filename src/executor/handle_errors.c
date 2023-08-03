#include "../../include/minishell.h"

void	error_exit_fork(t_shell *shell, char *input)
{
	ft_putstr_fd("function ", STDERR_FILENO);
	perror(input);
	ft_putstr_fd("failed\n", STDERR_FILENO);
	free_shell(shell);
	_exit(errno);
}

void	error_no_command(t_shell *shell, char *cmd)
{
	ft_putstr_fd("Shell_yeah: ", STDERR_FILENO);
	if(cmd != NULL)
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("command not found\n", STDERR_FILENO);
	free_shell(shell);
	_exit(127);
}

void	error_perm_denied(t_shell *shell, char *cmd)
{
	ft_putstr_fd("Shell_yeah: ", STDERR_FILENO);
	if(cmd != NULL)
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("permission denied\n", STDERR_FILENO);
	free_shell(shell);
	_exit(127);
}