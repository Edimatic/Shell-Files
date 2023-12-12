#include "eddi.h"

/**
 * compare_strings_ - Compare two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: 0 if strings are equal, non-zero otherwise.
 */
int compare_strings_(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
	str1++;
	str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

/**
 * string_length_ - Calculate the length of a string.
 * @str: The string.
 *
 * Return: The length of the string.
 */
size_t string_length_(const char *str)
{
		size_t length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}

/**
 * is_builtin - Check if the given command is a built-in command.
 * @command: The command to check.
 *
 * Return: 1 if the command is built-in, 0 otherwise.
 */
int is_builtin(char *command)
{
return (compare_strings(command, "exit") == 0 ||
compare_strings(command, "env") == 0 ||
compare_strings(command, "cd") == 0 ||
compare_strings(command, "setenv") == 0 ||
compare_strings(command, "unsetenv") == 0 ||
compare_strings(command, "alias") == 0);
}

/**
 * execute_builtin - Execute a built-in command.
 * @command: The built-in command to execute.
 * @running: A pointer to a flag indicating whether the shell is running.
 * @envp: The environment variables.
 * @aliases: The array of aliases.
 */
void execute_builtin(char *command, int *running, char **envp, Alias *aliases)
{
	if (compare_strings(command, "exit") == 0)
		execute_exit(running);
	else if (compare_strings(command, "env") == 0)
		execute_env(envp);
	else if (compare_strings(command, "setenv") == 0)
		execute_setenv(envp);
	else if (compare_strings(command, "unsetenv") == 0)
		execute_unsetenv(envp);
	else if (compare_strings(command, "cd") == 0)
		execute_cd(envp);
	else if (compare_strings(command, "alias") == 0)
		execute_alias_command(aliases, &alias_count);
	else
	{
		write(STDERR_FILENO, "Built-in command not found: ", 28);
		write(STDERR_FILENO, command, string_length(command));
		write(STDERR_FILENO, "\n", 1);
	}
}

