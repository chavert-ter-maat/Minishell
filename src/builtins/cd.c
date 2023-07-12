#include "../../include/minishell.h"

// relative path: indicates the path to the file or directory starting
// from the current location.
// absolute path: provides the complete path from the
// root directory or drive letter.

int	ft_cd(t_shell *shell, t_command *command)
{
	char *cwd;

	cwd = getcwd();
	if(!cwd)
		{
			ft_putchar_fd("cwd faked up", 1);
			exit(EXIT_FAILURE);
		}
	
}

/* 1. set new_working_dir:
'cd'				: change cwd to "HOME"
'cd -'				: change cwd to previous working directory (OLDPWD), ignore other arguments AND PRINT new cwd
'cd .'				: change cwd to current working directory aka does nothing
'cd ..'				: change cwd to directory 'above' cwd
'cd ~'				: change cwd to "HOME" of current user
'cd ~/path'			: change cwd to "HOME + path" of current user
'cd ~username'		: DOEN WE NIET
'cd relative path'	: change cwd to relative path
'cd absolute path'	: change cwd to absolute path

2. save current working directory into "OLDPWD=" in envp list

3. change cwd to new working directory with chdir()
chdir() = 0 indicates success: the operating system updates the process's current working directory

4. save new working directory into "PWD=" in envp list

*/