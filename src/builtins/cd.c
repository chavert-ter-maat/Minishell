#include "../../include/minishell.h"

// // relative path: indicates the path to the file or directory starting
// // from the current location.
// // absolute path: provides the complete path from the
// // root directory or drive letter.

	void	cd_error(char *argument)
	{
		ft_putstr_fd("cd: no such file or directory:",1);
		ft_putstr_fd(argument, 1);
		ft_putchar_fd('\n', 1);
	}

	char	*get_home_path(t_shell *shell)
	{
		char	*path;

		path = NULL;
		while (shell->env_list != NULL) 
		{
			if(ft_strnstr(shell->env_list->name, "HOME", 5))
			{
				path = shell->env_list->value;
				break ;
			}
			shell->env_list = shell->env_list->next;
		}
		if(!path)
			return(NULL);
		return(path);
	}


	static int	go_home(t_shell *shell)
	{
		char	*home_path;

		home_path = get_home_path(shell);
		if(!home_path)
			return(ERROR);
		if (chdir(home_path) == FAILED) // free cwd?
		{
			ft_putstr_fd("chdir failed", 1);
			perror("chdir failed");
			return(ERROR);
		}
		return(SUCCESS);
	}

	static int	go_previous_dir(char *cwd)
	{
		int		str_len;
		char	*new_path;

		new_path = NULL;
		str_len = ft_strlen(cwd) - 1;
		while(cwd[str_len])
		{
			if(cwd[str_len] == '/')
			{
				new_path = ft_strndup(cwd, str_len); //MALLOC!!
				break ;
			}
			str_len--;
		}
		if(!new_path)
			return(ERROR);
		return(chdir(new_path));		
	}
	static int	check_argument(char *argument, char *cwd, char *old_pwd)
	{
		if (ft_strncmp(argument, ".", 2) == 0)
			return (SUCCESS);
		if (ft_strncmp(argument, "..", 3) == 0)
			return (go_previous_dir(cwd));
		if (ft_strncmp(argument, "-", 2) == 0)
			return (chdir(old_pwd));
		return(chdir(argument));
	}	

	int	ft_cd(t_shell *shell, t_command *command)
	{
		char	*cwd;
		char	*old_pwd;

		cwd = NULL;
		cwd = getcwd(cwd, 0); //malloc!
		if(!cwd)
		{
			free(cwd);
			return(ERROR);
		}
		if(!command->args[1])
		{

			if(go_home(shell) == ERROR)
			{
				ft_putstr_fd("go_home() failed", 1);
				return(ERROR);
			}
			return(SUCCESS);
		}
		old_pwd = cwd;
		if(check_argument(command->args[1], cwd, old_pwd) == -1)
			cd_error(command->args[1]);
		return(SUCCESS);
	}

// /* 1. set new_working_dir:
// 'cd'				: change cwd to "HOME"
// 'cd -'				: change cwd to previous working directory (OLDPWD), ignore other arguments AND PRINT new cwd
// 'cd .'				: change cwd to current working directory aka does nothing
// 'cd ..'				: change cwd to directory 'above' cwd
// 'cd ~'				: change cwd to "HOME" of current user
// 'cd ~/path'			: change cwd to "HOME + path" of current user
// 'cd ~username'		: DOEN WE NIET
// 'cd relative path'	: change cwd to relative path
// 'cd absolute path'	: change cwd to absolute path

// 2. save current working directory into "OLDPWD=" in envp list

// 3. change cwd to new working directory with chdir()
// chdir() = 0 indicates success: the operating system updates the process's current working directory

// 4. save new working directory into "PWD=" in envp list

// */