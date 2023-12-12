#include "eddi.h"

/**
 * read_command - Read a command from the standard input.
 *
 * Return: The command string.
 */
char *read_command(void)
{
		char *line = NULL;
		size_t len = 0;
		size_t line_len;

	if (getline(&line, &len, stdin) == -1)
	{
	write(1, "Exiting the shell...\n", 21);
	free(line);
	exit(EXIT_SUCCESS);
	}

/* Remove the newline character at the end of the line*/
	line_len = custom_strlen(line);
	if (line_len > 0 && line[line_len - 1] == '\n')
	{
	line[line_len - 1] = '\0';
	}
	return (line);
}

