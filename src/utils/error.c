#include "../../include/minishell.h"

void	error_free_exit(t_shell *shell)
{
	t_var	*var;

	printf("ERROR MESSAGE!\n");//add error message
	if (shell->cmd_line)
		free(shell->cmd_line);
	free_list(shell->lexer);
	free_list(shell->expander);
	while (shell->var_list)
	{
		var = shell->var_list;
		shell->var_list = shell->var_list->next;
		if (var->name)
			free(var->name);
		if (var->value)
			free(var->value);
		free(var);
	}
	exit(EXIT_FAILURE);
}