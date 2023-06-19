#include "../../include/minishell.h"

void	input_handling(t_shell *shell, int argc, char **argv, char **envp)
{
	ft_bzero(shell, sizeof(shell));
	shell->argc = argc;
	shell->argv = argv;
	shell->envp = envp;
	shell->infile = argv[1];
	shell->outfile = argv[3];
}
