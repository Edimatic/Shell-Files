#include "eddi.h"

/**
 * print_env - Print the current environment.
 * @envp: The environment variables.
 */
void print_env(char **envp)
{
	int i = 0;

while (envp[i] != NULL)
	{
	write(1, envp[i], custom_strlen(envp[i]));
	write(1, "\n", 1);
		i++;
	}
}
