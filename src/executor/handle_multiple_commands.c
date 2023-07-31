#include "../../include/minishell.h"

// former read end becomes read end.
static int handle_fds(t_shell *shell, int *pipe_fd, int read_end)
{
    if (close(pipe_fd[WRITE_END]) == FAILED)
    {
        ft_putstr_fd("hier1\n", 1);
        perror_exit(shell, "close");
    }
    if (read_end != STDIN_FILENO)
    {
        if (close(read_end) == FAILED)
        {
            ft_putstr_fd("hier2\n", 1);
            perror_exit(shell, "close");
        }
    }
    read_end = pipe_fd[READ_END];
    return (read_end);
}

// executes the command and writes the output of the command to the write end
// of the pipe.
void execute_non_builtin_fork(t_shell *shell, t_command *command, int read_end, int *pipe_fd)
{
    pid_t pid = fork();
    if (pid == FAILED)
        perror_exit(shell, "fork");
    if (pid == SUCCESS)
    {
        if (dup2(read_end, STDIN_FILENO) == FAILED)
        {
            ft_putstr_fd("dub test3\n", 1);
            perror_exit(shell, "dup2");
        }
        if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == FAILED)
        {
            ft_putstr_fd("dub test2\n", 1);
            perror_exit(shell, "dup2");
        }
        execute_non_builtin(shell, command);
    }
    if (close(pipe_fd[WRITE_END]) == FAILED)
    {
        ft_putstr_fd("hier4\n", 1);
        perror_exit(shell, "close");
    }
}

// creates forks for the amount of commands and pipes the output of a
// command to the input of the next command.
static int initiate_forks(t_shell *shell, t_list *command_list)
{
    int pipe_fd[2];
    int read_end = 0;
    t_node *current = command_list->head;
    while (current->next)
    {
        if (pipe(pipe_fd) == FAILED)
            perror_exit(shell, "pipe");

        if (check_if_builtin(current->data->args[0]) == TRUE)
        {
            execute_childs(shell, current->data, read_end, pipe_fd);
        }
        else
        {
            execute_non_builtin_fork(shell, current->data, read_end, pipe_fd);
        }

        read_end = handle_fds(shell, pipe_fd, read_end);
        current = current->next;
    }

    pid_t pid = fork();
    if (pid == FAILED)
        perror_exit(shell, "fork");

    if (pid == SUCCESS)
    {
        if (dup2(read_end, STDIN_FILENO) == FAILED)
        {
            ft_putstr_fd("dub test3\n", 1);
            perror_exit(shell, "dup2");
        }
        execute_non_builtin(shell, current->data);
    }

    if (close(read_end) == FAILED)
    {
        ft_putstr_fd("hier3\n", 1);
        perror_exit(shell, "close");
    }

    return pid;
}

void handle_multiple_commands(t_shell *shell)
{
    pid_t pid = initiate_forks(shell, shell->command_list);
    if (waitpid(pid, NULL, 0) == FAILED)
        perror_exit(shell, "waitpid");
}
