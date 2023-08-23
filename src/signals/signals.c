/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 14:58:02 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/23 16:44:56 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	sig_handler_prompt(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 1;		
	}
}

static void	sig_handler_executor(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		g_status = 130;
	}
	if (signum == SIGQUIT)
	{
		rl_replace_line("", 0);
		ft_putendl_fd("Quit :3", 1);
		rl_on_new_line();
		g_status = 131;
	}
}
static void	sig_handler_heredoc(int signum)
{
	if (signum == SIGINT)
		_exit(1);
}

void	eof_handler(t_shell *shell)
{
	ft_putstr_fd("exit\n", 1);
	shell->status = 0;
	clean_exit(shell);
}

void	init_signals(int mode)
{
	signal(SIGTSTP, SIG_IGN);
	if (mode == PROMPT)
	{
		signal(SIGINT, &sig_handler_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == EXECUTOR)
	{
		signal(SIGINT, &sig_handler_executor);
		signal(SIGQUIT, &sig_handler_executor);
	}
	if (mode == HEREDOC)
	{
		signal(SIGINT, &sig_handler_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
