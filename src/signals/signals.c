#include "../../include/minishell.h"

void	sigint_handler(int signum)
{
	
	(void)	signum;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	sigquit_handler(t_shell *shell)
{
	ft_putstr_fd("exit\n", 1);
	ft_exit(shell, 0);
}

void	init_signals(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
