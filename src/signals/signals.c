/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 14:58:02 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/16 14:58:03 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	sigint_handler_prompt(int signum)
{
	(void) signum;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 1;
}

void	sigint_handler(int signum)
{
	(void) signum;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	g_status = 130;
}

void	sigquit_handler(int signum)
{
	(void) signum;
	rl_replace_line("", 0);
	ft_putendl_fd("Quit :3", 1);
	rl_on_new_line();
	g_status = 131;
}

void	eof_handler(t_shell *shell)
{
	ft_putstr_fd("exit\n", 1);
	g_status = 0;
	clean_exit(shell);
}

void	init_signals(void)
{
	signal(SIGINT, &sigint_handler_prompt);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
