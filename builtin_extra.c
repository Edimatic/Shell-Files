#include "eddi.h"

/**
 * execute_cd - Execute the cd builtin command.
 * @envp: The environment variables.
 */
void execute_cd(char **envp)
{
char *path = strtok(NULL, " \t\n");

	if (path != NULL)
{
	if (chdir(path) == 0)
	{
		set_env_variable("PWD", getcwd(NULL, 0), &envp);
	}
	else
	{
		perror("cd");
	}
	}
	else
{
		write(2, "Usage: cd DIRECTORY\n", 20);
	}
}

/**
 * execute_alias_command - Execute the alias builtin command.
 * @aliases: The array of aliases.
 * @alias_count: The number of aliases.
 */
void execute_alias_command(Alias *aliases, int *alias_count)
{
	char *arguments = strtok(NULL, "");

	execute_alias(arguments, aliases, alias_count);
}

