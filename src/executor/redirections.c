#include "../../include/minishell.h"

static void	redir_in(char *file, char *flag)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd == FAILED)
	{
		perror_return_promt(file);
		return ;
	}
	if(ft_strncmp("YES_COMMAND", flag, 12) == 0)
		change_fd_to_in(fd);
	return ;
}

// redirects stfout to file
static void	redir_out(char *file, char *flag)
{
	int fd;
	
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == FAILED)
	{
		perror_return_promt(file);
		return ;
	}
	if(ft_strncmp("YES_COMMAND", flag, 12) == 0)
		change_fd_to_out(fd);
	return ;
}

static void	redir_append(char *file, char *flag)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == FAILED)
	{
		perror_return_promt(file);
		return ;
	}
	if (ft_strncmp("YES_COMMAND", flag, 12) == 0)
		change_fd_to_out(fd);
	return ;
}

static int	handle_redir(t_shell *shell,t_redir *redir, char *flag)
{
	if (redir->type == IN)
	{
		redir_in(redir->file, flag);
		return (FOUND);
	}
	if (redir->type == OUT)
	{
		redir_out(redir->file, flag);
		return (FOUND);
	}
	if (redir->type == HEREDOC)
	{
		handle_here_doc(shell, redir->file, flag);
		return (FOUND);
	}
	if (redir->type == APPEND)
	{
		redir_append(redir->file, flag);
		return (FOUND);
	}
	return (NOT_FOUND);
}

void	handle_redirection(t_shell *shell, t_command *command, char *flag)
{
	t_node	*node;

	node = command->redir_list->head;
	while (node)
	{
		if (handle_redir(shell, node->data, flag) == FOUND)
			return ;
		node = node->next;
	}
	return ;
}
