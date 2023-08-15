#include "../../include/minishell.h"

static char	*strjoin_env_var(t_var *var)
{
	int		len;
	char	*str;

	len = ft_strlen(var->name);
	len += ft_strlen(var->value) + 2;
	str = ft_calloc(len, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcat(str, var->name, len + 2);
	ft_strlcat(str, "=", len + 2);
	ft_strlcat(str, var->value, len + 2);
	return (str);
}

void	update_env(t_shell *shell)
{
	char	**new_env;
	int		i;
	t_node	*node;

	new_env = ft_calloc(shell->environment->count + 1, sizeof(char *));
	i = 0;
	node = shell->environment->head;
	while (node && i < shell->environment->count)
	{
		new_env[i] = strjoin_env_var(node->data);
		if (!new_env[i])
		{
			shell_error(shell, malloc_error, "update_env", NULL, 1);
			ft_free_2d_array(&new_env);
			free_shell(shell);
			_exit(g_status);
		}
		i++;
		node = node->next;
	}
	ft_free_2d_array(&shell->envp);
	shell->envp = new_env;
}
