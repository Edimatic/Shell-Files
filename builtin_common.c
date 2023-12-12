#include "eddi.h"

/**
 * execute_exit - Execute the exit builtin command.
 * @running: A pointer to a flag indicating whether the shell is running.
 */
void execute_exit(int *running)
{
		char *arg = strtok(NULL, " \t\n");
		int status = (arg != NULL) ? atoi(arg) : 0;
		char status_str[10];

	write(1, "Exiting the shell with status ", 30);
	snprintf_custom(status_str, sizeof(status_str), "%d", status);
	write(1, status_str, strlen_custom(status_str));
	write(1, "...\n", 4);

		*running = 0;
		_exit(status);
}

/**
 * execute_env - Execute the env builtin command.
 * @envp: The environment variables.
 */
void execute_env(char **envp)
{
	print_env(envp);
}

/**
 * execute_setenv - Execute the setenv builtin command.
 * @envp: The environment variables.
 */
void execute_setenv(char **envp)
{
		char *name = strtok(NULL, " \t\n");
		char *value = strtok(NULL, " \t\n");

	if (name != NULL && value != NULL)
{
	if (set_env_variable(name, value, &envp) == 0)
{
	write(1, "Environment variable set: ", 26);
	write(1, name, strlen_custom(name));
	write(1, "=", 1);
	write(1, value, strlen_custom(value));
	write(1, "\n", 1);
}
	else
	{
		write(2, "Failed to set environment variable\n", 36);
	}
	}
	else
	{
		write(2, "Usage: setenv VARIABLE VALUE\n", 29);
	}
}

/**
 * execute_unsetenv - Execute the unsetenv builtin command.
 * @envp: The environment variables.
 */
void execute_unsetenv(char **envp)
{
		char *name = strtok(NULL, " \t\n");

	if (name != NULL)
	{
	if (unset_env_variable(name, &envp) == 0)
	{
	write(1, "Environment variable unset: ", 28);
	write(1, name, strlen_custom(name));
	write(1, "\n", 1);
}
	else
	{
		write(2, "Failed to unset environment variable\n", 38);
	}
}
	else
	{
		write(2, "Usage: unsetenv VARIABLE\n", 25);
	}
}
/**
 * strlen_custom - Custom implementation of the strlen function.
 * @str: The string to calculate the length of.
 *
 * Return: The number of characters in the string.
 */
size_t strlen_custom(const char *str)
{
	size_t len = 0;

	while (*str != '\0')
	{
		len++;
		str++;
	}

		return (len);
}

