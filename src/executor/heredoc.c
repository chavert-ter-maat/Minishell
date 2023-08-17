/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:06:17 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/08/17 16:35:16 by cter-maa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*note to self: dit werkt nu alleen in een child proces..
HOe fix ik dat dit altijd werkt? en exit code is ook gek.
is signal(SIGINT, SIG_DFL) niet t zelfde?
*/

static void	sigint_handler_heredoc(int signum)
{
	(void) signum;
	_exit(1);
}

static void	init_signals_heredoc(void)
{
	signal(SIGINT, &sigint_handler_heredoc);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int	write_to_pipe(t_shell *shell, char *delimiter)
{
	int		pipe_fd[2];
	char	*line;
	
	if (pipe(pipe_fd) == FAILED)
		perror_exit_fork(shell, "pipe"); //check for right exit!!!!
	line = readline("> ");
	while (line && !(ft_strncmp(line, delimiter,
				ft_strlen(delimiter) + 1) == 0))
	{
		write(pipe_fd[WRITE_END], line, ft_strlen(line));
		write(pipe_fd[WRITE_END], "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (line)
		free (line);
	if (close(pipe_fd[WRITE_END]) == FAILED)
		perror_exit_fork(shell, "close");
	return (pipe_fd[READ_END]);
}

void	create_heredoc(t_shell *shell, t_redir *redir)
{
	if (!redir->file || redir->file[0] == '\0')
	{
		shell_error(shell, syntax_error, "\\n", 139);
		return ;
	}
	init_signals_heredoc();
	redir->heredoc_read_end = write_to_pipe(shell, redir->file);
}
