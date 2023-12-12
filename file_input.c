#include "eddi.h"

/**
 * custom_fopen - Custom implementation of fopen function.
 * @pathname: The path to the file to be opened.
 * @mode: The mode for opening the file.
 *
 * Return: Pointer to the FILE stream on success, NULL on failure.
 */
FILE *custom_fopen(const char *pathname, const char *mode)
{
	FILE *file = custom_fopen(pathname, mode);

	if (file == NULL)
	{
	perror("Error opening file");
	}

	return (file);
}
/**
 * custom_fclose - Custom implementation of fclose function.
 * @stream: Pointer to the FILE stream to be closed.
 *
 * Return: 0 on success, EOF on failure.
 */
int custom_fclose(FILE *stream)
{
	int result = custom_fclose(stream);

	if (result == EOF)
	{
	perror("Error closing file");
	}

		return (result);
}
/**
 * custom_strchr - Custom implementation of strchr function.
 * @str: The string to be searched.
 * @ch: The character to search for.
 *
 * Return: A pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */
char *custom_strchr(const char *str, int ch)
{
/* Custom implementation code here */
	while (*str != '\0')
	{
	if (*str == ch)
	{
		return ((char *)str);
	}
	str++;
	}
		return (NULL);
}

/**
 * execute_commands_file - The main function that open command file.
 * @filename: Pointer to the file location.
 * @envp: The pointer showing the environmental veriable.
 * @running: Notation of the running file.
 */

void execute_commands_file(const char *filename, char **envp, int *running)
{
	char *newline, *command = NULL;
	size_t len = 0;
	FILE *file = custom_fopen(filename, "r");

	if (file == NULL)
	{
	perror("Error opening file");
return;
	}
while (getline(&command, &len, file) != -1)
	{
/* Trim newline character from the end */
	newline = custom_strchr(command, '\n');
	if (newline != NULL)
	*newline = '\0';
	if (custom_strlen(command) > 0)
	{
	if (is_builtin(command))
	{
		execute_builtin(command, running, envp, aliases);
	}
	else if (custom_strcmp(command, "exit") == 0)
	{
		write(1, "Exiting the shell...\n", 21);
		*running = 0;
		}
	else
		{
		execute_command(command, envp, running);
	}
	}
	}
		free(command);
		custom_fclose(file);
}
