#include "../../include/minishell.h"

void	free_shell(t_shell *shell)
{
	if (shell->cmd_line)
	{
		free(shell->cmd_line);
		shell->cmd_line = NULL;
	}
	shell->token_list = free_list(shell->token_list);
	shell->command_list = free_list(shell->command_list);
}
