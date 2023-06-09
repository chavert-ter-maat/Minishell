#include "../../include/minishell.h"
#include "../../include/execute.h"

static void	execute_single_child(t_pipex *generate)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit("error");
	if (pid == 0)
	{
		run_commands(generate, generate->argv2, generate->cmd1);
	}
	else
		exit(error);
}

void	execute_single_command(t_minishell *mini)
{
	t_cmd	*current_cmd;

	current_cmd = mini->cmd_list;
	if (current_cmd->args[0] == NULL)
		exit(error);
	if (current_cmd->args[0] == NULL)
		handle_redirect(current_cmd->redir, mini_error_test);
	execute_single_child(current_cmd, mini);
}
