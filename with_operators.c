#include "eddi.h"

/**
 * str_copy - Copy a string.
 * @dest: Destination buffer.
 * @src: Source string.
 */
void str_copy(char *dest, const char *src)
{
	while ((*dest++ = *src++))
	;
}

/**
 * str_compare - Compare two strings.
 * @str1: First string.
 * @str2: Second string.
 *
 * Return: 0 if strings are equal, non-zero otherwise.
 */
int str_compare(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

/**
 * execute_command_with_operators - The function execute operator
 * @command: Command to be executed
 * @envp: Pointing to environmental variables
 * @running: Running the program
 */
void execute_command_with_operators(char *command, char **envp, int *running)
{
	char *token, command_copy[512];

	str_copy(command_copy, command);
token = strtok(command_copy, " \t\n"); /* Tokenize the copied command string */
while (token != NULL) /* Check for operators */
{
if (str_compare(token, "&&") == 0) /* Handle && */
	{
token = strtok(NULL, " \t\n"); /*Execute next command only if the 1st succeed*/
	if (token != NULL)
	{
	execute_command(token, envp, running);
		if (*running == 0)
		{
		return;
		}
	}
}
else if (str_compare(token, "||") == 0) /* Handle || */
	{
token = strtok(NULL, " \t\n"); /*Execute next command only if the 1st failed */
	if (token != NULL)
	{
	execute_command(token, envp, running);
		if (*running == 1)
		{
			return;
		}
	}
}
	else
{
	execute_command(token, envp, running); /* Regular command */
	if (*running == 0)
{
		return; /* Command failed, stop executing further commands */
}
	}
		token = strtok(NULL, " \t\n"); /* Get the next token */
	}
}

