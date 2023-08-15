#include "../../include/minishell.h"

static void	redir_in(char *file, t_command *command, pid_t pid)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd == FAILED)
	{
		perror_return_promt(file);
		if (pid == 0)
			_exit(1);
		return ;
	}
	if (command->arg_list->count > 0)
		change_fd_to_in(fd);
}

// redirects stfout to file
static void	redir_out(char *file, t_command *command, pid_t pid)
{
	int fd;
	
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == FAILED)
	{
		perror_return_promt(file);
		if (pid == 0)
			_exit(1);
		return ;
	}
	if (command->arg_list->count > 0)
		change_fd_to_out(fd);
}

static void	redir_append(char *file, t_command *command, pid_t pid)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == FAILED)
	{
		perror_return_promt(file);
		if (pid == 0)
			_exit(1);
		return ;
	}
	if (command->arg_list->count > 0)
		change_fd_to_out(fd);
}

static void	handle_redir(t_shell *shell, t_command *command, t_redir *redir, pid_t pid)
{
	if (redir->type == IN)
		return (redir_in(redir->file, command, pid));
	if (redir->type == OUT)
		return (redir_out(redir->file, command, pid));
	if (redir->type == HEREDOC)
		return (handle_here_doc(shell, command, redir->file));
	if (redir->type == APPEND)
		return (redir_append(redir->file, command, pid));
}

void	handle_redirection(t_shell *shell, t_command *command, pid_t pid)
{
	t_node	*node;

	node = command->redir_list->head;
	while (node)
	{
		handle_redir(shell, command, node->data, pid);
		node = node->next;
	}
}
