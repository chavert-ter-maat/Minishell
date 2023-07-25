#include "../../include/minishell.h"

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
		write(1, "exit\n", 5);
	exit(SUCCESS);
}

void	sigquit_handler(int signum)
{
	if (signum == SIGQUIT)
		write(1, "quit", 4);
	else
		write(1, "else", 4);
	exit(SUCCESS);
}

void	ft_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
