#include "../../include/minishell.h"

void	sigint_handler(int signum)
{
	
	(void)	signum;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit_handler(t_shell *shell)
{
	ft_putstr_fd("exit\n", 1);
	shell->return_value = 0;
	clean_exit(shell);
}

void	init_signals(void)
{
	signal(SIGINT, &sigint_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}


