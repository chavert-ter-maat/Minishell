#include "../../include/minishell.h"
#include "../../include/execute.h"

void execute_multiple_commands(t_struct)
{
	int 	pipe_fd[2];
	int		amount_children;
	int		pipe_read_end;
	t_struct	*current_node;

	amount_children = 0;
	pipe_read_end = STDIN_FILENO;
	current_node =  t_struct->link_list_commands;
	while(current_node)
	{
		
		amount_children++;
		current_node = current_node->next;
	}

}