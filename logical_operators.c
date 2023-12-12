#include "eddi.h"

/**
 * compare_strings - Compare two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: 0 if strings are equal, non-zero otherwise.
 */
int compare_strings(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
		{
		str1++;
		str2++;
	}
		return (*(unsigned char *)str1 - *(unsigned char *)str2);
}
/**
 * handle_logical_operators - Function to execute logical operators
 * @command: Pointer to the execute command.
 * @envp: Environmental variable pointer.
 * @running: Running process.
 */
void handle_logical_operators(char *command, char **envp, int *running)
{
	char *token = strtok(command, "&&");
	int or_operator, and_operator =
		(token != NULL && compare_strings(token, "") != 0);

	token = strtok(NULL, "&");
	or_operator = (token != NULL && compare_strings(token, "") != 0);

	if (and_operator || or_operator)
	{
		execute_command(command, envp, running); /* Execute the first command */
		if ((*running && and_operator) || (!(*running) && or_operator))
		{
			token = strtok(NULL, "&&");
			if (token != NULL)
				execute_command(token, envp, running);
		}
	}
	else
	{
		if (is_builtin(command) || compare_strings(command, "exit") == 0)
		{
			execute_builtin(command, running, envp, aliases);
		}
		else
		{
			execute_command(command, envp, running);
		}
	}
}

