#include "../../include/minishell.h"

void	sigint_handler(int signum)
{
	(void)	signum;
	// rl_replace_line("", 0);
	// rl_on_new_line();
}

void	sigquit_handler(t_shell *shell)
{
	printf("exit\n");
	ft_exit(shell);
	exit(SUCCESS);
}

void	ft_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
