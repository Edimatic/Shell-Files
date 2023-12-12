#include "eddi.h"

/**
 * cd_builtin - Change the current directory of the process.
 * @path: The path to change to. If NULL, change to $HOME.
 * @envp: The environment variables.
 */
void cd_builtin(char *path, char ***envp)
{
	char *prev_dir, *home_dir, *old_pwd, *current_dir;

	home_dir = custom_getenv("HOME", *envp);
	if (home_dir == NULL)
{
	custom_fprintf_stderr("cd: $HOME not set\n");
		return;
	}
	old_pwd = custom_getcwd(NULL, 0);
	if (path == NULL)
	path = home_dir;
	else if (custom_strcmp(path, "-") == 0)
	{
	prev_dir = custom_getenv("OLDPWD", *envp);
	if (prev_dir != NULL)
{
	path = prev_dir;
	write(1, path, custom_strlen(path));
	write(1, "\n", 1);
}
	else
	{
	custom_fprintf_stderr("cd: OLDPWD not set\n");
		return;
	}
}
	if (chdir(path) == -1)
	perror("cd");
	else
	{
		current_dir = custom_getcwd(NULL, 0);
		set_env_variable("OLDPWD", old_pwd, envp);
		set_env_variable("PWD", current_dir, envp);
		free(old_pwd);
		free(current_dir);
	}
}

