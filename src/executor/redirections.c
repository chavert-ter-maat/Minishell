#include "../../include/minishell.h"

// redirects file to stdin
static int	redir_in(t_shell *shell, t_command *command, char *file, char *f)
{
	command->read_fd = open(file, O_RDONLY);
	if (command->read_fd == FAILED)
	{
		perror_return_promt(shell, file);
		return (ERROR);
	}
	if(ft_strncmp("YES_COMMAND", f, 12) == 0)
	{
		if (dup2(command->read_fd, STDIN_FILENO) == FAILED)
		{
			ft_putstr_fd ("fix error function", 1); 
			_exit (1);
		}
		if (close (command->read_fd) == FAILED)
		{
			ft_putstr_fd ("fix error function", 1); 
			_exit (1);
		}
	}
	return (SUCCESS);
}

// redirects stfout to file
int	redir_out(t_shell *shell, t_command *command, char *file, char *f)
{
	command->write_fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (command->write_fd == FAILED)
	{
		perror_return_promt(shell, file);
		return (FAILED);
	}
	if(ft_strncmp("YES_COMMAND", f, 12) == 0)
	{
		if (dup2(command->write_fd, STDOUT_FILENO) == FAILED)
		{
			ft_putstr_fd ("fix error function", 1); 
			_exit(1);
		}
		if (close(command->write_fd) == FAILED)
		{
			ft_putstr_fd("fix error function", 1); 
			_exit (1);
		}
	}
	return (SUCCESS);
}

static int	redir_append(t_shell *shell, t_command *command, char *file, char *f)
{
	command->write_fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (command->write_fd == FAILED)
	{
		perror_return_promt(shell, file);
		return (1) ;
	}
	if(ft_strncmp("YES_COMMAND", f, 12) == 0)
	{
		if (dup2(command->write_fd, STDOUT_FILENO) == FAILED)
		{
			ft_putstr_fd ("fix error function", 1); 
			_exit(1);
		}
		if (close(command->write_fd) == FAILED)
		{
			ft_putstr_fd("fix error function", 1); 
			_exit (1);
		}
	}
	return (0);
}

static int	handle_redir(t_shell *shell, t_command *command, t_redir *redir, char *f)
{
	if (redir->type == IN)
	{
		redir_in(shell, command, redir->file, f);
		return (FOUND);
	}
	if (redir->type == OUT)
	{
		redir_out(shell, command, redir->file, f);
		return (FOUND);
	}
	if (redir->type == HEREDOC)
	{
		handle_here_doc(shell, command, redir->file, f);
		return (FOUND);
	}
	if (redir->type == APPEND)
	{
		redir_append(shell, command, redir->file, f);
		return (FOUND);
	}
	return (NOT_FOUND);
}

int	check_if_redir(t_shell *shell, t_command *command, char *flag)
{
	t_node	*node;

	node = command->redir_list->head;
	while (node)
	{
		if (handle_redir(shell, command, node->data, flag) == FOUND)
			return (FOUND);
		node = node->next;
	}
	return (NOT_FOUND);
}
