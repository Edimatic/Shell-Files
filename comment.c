#include "eddi.h"

/**
 * find_comment_position - Find the position of the comment symbol '#' in a str
 *
 * @str: The string to search.
 *
 * Return: A pointer to the position of '#' or NULL if not found.
 */
char *find_comment_position(char *str)
{
	char *token = strtok(str, "#");

	return ((token != NULL) ? token : NULL);
}

/**
 * remove_comments - Remove comments from a command string.
 *
 * @command: The command string.
 */
void remove_comments(char *command)
{
		char *comment_position = find_comment_position(command);

if (comment_position != NULL)
	{
*comment_position = '\0'; /*Null terminate the string at the comment position*/
	}
}

/**
 * custom_putenv - Custom implementation of the putenv function.
 * @str: The string to set as an environment variable in the form "NAME=VALUE".
 *
 * Return: 0 on success, -1 on failure.
 */
int custom_putenv(char *str)
{
	return (putenv(str));
}

/**
 * custom_unsetenv - Unset an environment variable.
 * @name: The name of the environment variable to unset.
 *
 * Return: 0 on success, -1 on failure.
 */
int custom_unsetenv(const char *name)
{
	return (unsetenv(name));
}

/**
* custom_free - Custom implementation of the free function.
* @ptr: A pointer to the memory block to be freed.
*/
	void custom_free(void *ptr)
{
	free(ptr);
}

