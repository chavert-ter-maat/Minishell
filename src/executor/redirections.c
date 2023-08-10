#include "../../include/minishell.h"

// redirects stdout to file.
void redir_in(t_command *command, char *file)
{
	command->read_fd = open(file, O_RDONLY);
	if (command->read_fd == FAILED)
	{
		ft_putstr_fd("fix error function", 1); //Fix error!!
		_exit(1);
	}
	if (dup2(command->read_fd, STDIN_FILENO) == FAILED)
	{
		ft_putstr_fd("fix error function", 1); //Fix error!!
		_exit(1);
	}
	if (close(command->read_fd) == FAILED)
	{
		ft_putstr_fd("fix error function", 1); //Fix error!!
		_exit(1);
	}
}

// redirects stfout to file
void	redir_out(t_command *command, char *file)
{
	command->write_fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (command->write_fd == FAILED)
	{
		ft_putstr_fd("fix error function", 1); //Fix error!!
		_exit(1);
	}
	if (dup2(command->write_fd, STDOUT_FILENO) == FAILED)
	{
		ft_putstr_fd("fix error function", 1); //Fix error!!
		_exit(1);
	}
	if (close(command->write_fd) == FAILED)
	{
		ft_putstr_fd("fix error function", 1); //Fix error!!
		_exit(1);
	}
}

int	redir_append(t_command *command, char *file)
{
	command->write_fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (command->write_fd == FAILED)
	{
		ft_putstr_fd("fix error function", 1); //Fix error!!
		_exit(1);
	}
	if (dup2(command->write_fd, STDOUT_FILENO) == FAILED)
	{
		ft_putstr_fd("fix error function", 1); //Fix error!!
		_exit(1);
	}
	if (close(command->write_fd) == FAILED)
	{
		ft_putstr_fd("fix error function", 1); //Fix error!!
		_exit(1);
	}
	return (0);
}

static int	handle_redir(t_shell *shell, t_command *command, t_redir *redir)
{
	if (redir->type == IN)
	{
		redir_in(command, redir->file);
		return(FOUND);
	}
	if (redir->type == OUT)
	{
		redir_out(command, redir->file);
		return(FOUND);
	}
	if (redir->type == HEREDOC)
	{
		handle_here_doc(shell, command, redir->file);
		return(FOUND);
	}
	if (redir->type == APPEND)
	{
		redir_append(command, redir->file);
		return(FOUND);
	}
	return(NOT_FOUND);
}

int	check_if_redir(t_shell *shell, t_command *command)
{
	t_node *node;
	ft_putstr_fd("komt ie hier?\n", 1);
	if (command->redir_list->count == 0)
		return(NOT_FOUND);
	node = command->redir_list->head;
	while (node)
	{
		if(handle_redir(shell, command, node->data) == FOUND)
			return(FOUND);
		node = node->next;
	}
	return(NOT_FOUND);
}