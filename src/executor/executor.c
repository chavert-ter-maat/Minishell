#include "../../include/minishell.h"

void	executor(t_shell *shell)
{
	t_command	*command;
	
	if (!shell->command_list || shell->command_list->count == 0)
		return ;
	command = shell->command_list->head->data;
	if(command->arg_list->count == 0 && command->redir_list)
	{
		check_if_redir(shell, shell->command_list->head->data, "NO_COMMAND");
		return ;
	}
	if (shell->command_list->count == 1)
		handle_single_command(shell, shell->command_list->head->data);
	else
		handle_multiple_commands(shell);
	return ;
}

