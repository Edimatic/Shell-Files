#include "eddi.h"

Alias *aliases;
int alias_count = 0;

/**
 * str_length - Calculate the length of a string.
 * @str: The string to calculate the length for.
 *
 * Return: The length of the string.
 */
size_t str_length(const char *str)
{
		size_t length = 0;

	while (str[length] != '\0')
	{
	length++;
	}
		return (length);
}

/**
 * main - Main function to be executed.
 * @argc: Argument count.
 * @argv: Argument vector.
 * @envp: Pointing to environmental variable.
 *
 * Return: 0 on successful execution, non-zero on failure.
 */
int main(int argc __attribute__((unused)),
	char **argv __attribute__((unused)), char **envp)
{
		char *command;
		int running = 1; /*Flag to indicate whether the shell is running */
		char *trimmed_command;
		char *token;

	while (running)
{
		display_prompt();
	command = read_command();

/* Allocate memory for aliases */
	aliases = malloc(sizeof(Alias) * MAX_ALIASES);

/* Tokenize commands separated by ';' */
	token = strtok(command, ";");
	while (token != NULL)
{
/* Trim leading and trailing whitespaces */
	trimmed_command = trim_whitespace(token);
	if (str_length(trimmed_command) > 0)
{
	handle_logical_operators(trimmed_command, envp, &running);
}
/* Move to the next command */
	token = strtok(NULL, ";");
	free(trimmed_command); /* Free memory allocated by trim_whitespace */
}
	free(command);
	}
	free(aliases); /* Free memory allocated for aliases */
		return (0);
}

