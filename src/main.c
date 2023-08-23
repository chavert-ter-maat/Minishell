/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cter-maa <cter-maa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/23 17:07:24 by cter-maa      #+#    #+#                 */
/*   Updated: 2023/08/23 17:07:28 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <signal.h>

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argv;
	if (argc > 1)
		exit(1);
	init_shell(&shell, envp);
	while (1)
	{
		init_signals(PROMPT);
		shell.cmd_line = readline("shellyeah$ ");
		if (shell.cmd_line == NULL)
			eof_handler(&shell);
		add_history(shell.cmd_line);
		parser(&shell);
		executor(&shell);
		free_shell(&shell);
	}
	return (0);
}
