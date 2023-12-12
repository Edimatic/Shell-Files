#include "eddi.h"

/**
 * replace_variables - Replace variables in the command string.
 * @command: The command string.
 * @status: The exit status of the last command.
 * @pid: The process ID of the shell.
 *
 * Return: A new string with variables replaced.
 */
char *replace_variables(char *command, int status, pid_t pid)
{
	char *result = malloc(string_length(command) + 1);/*Create a copy to modify*/
	char pid_str[10];

/* Replace $? with exit status */
	char status_str[10];

	itoa(status, status_str);
	result = replace_str(result, "$?", status_str);

/* Replace $$ with process ID */
	itoa(pid, pid_str);
	result = replace_str(result, "$$", pid_str);

		return (result);
}

/**
 * replace_str - Replace all occurrences of a substring in a string.
 * @str: The original string.
 * @old_str: The substring to replace.
 * @new_str: The replacement substring.
 *
 * Return: A new string with replacements.
 */
char *replace_str(char *str, const char *old_str, const char *new_str)
{
		char *result;
		int i = 0, j = 0;

/* Allocate memory for the new string */
	result = (char *)malloc(strlen(str) + 1);
	if (result == NULL)
	{
	perror("malloc");
	exit(EXIT_FAILURE);
}
	while (str[i] != '\0')
	{
		int match = 1;
		int k;

	for (k = 0; old_str[k] != '\0'; ++k)
	{
	if (str[i + k] != old_str[k])
		{
		match = 0;
		break;
	}
}
	if (match)
{
	for (k = 0; new_str[k] != '\0'; ++k)
	{
	result[j++] = new_str[k];
	}
	i += k;
}
	else
	{
		result[j++] = str[i++];
		}
	}

	result[j] = '\0';
	return (result);
}

/**
 * itoa - Convert an integer to a string.
 * @num: The integer to convert.
 * @str: The buffer to store the resulting string.
 */
void itoa(int num, char *str)
{
		int i = 0;

		if (num == 0)
{
		str[i++] = '0';
}
	else
	{
	while (num != 0)
{
	int digit = num % 10;

	str[i++] = digit + '0';
	num = num / 10;
		}
	}
		str[i] = '\0';
		reverse_str(str);
}

/**
 * reverse_str - Reverse a string in place.
 * @str: The string to reverse.
 */
void reverse_str(char *str)
{
		int length = string_length(str);
		int i, j;

	for (i = 0, j = length - 1; i < j; ++i, --j)
{
		char temp = str[i];

		str[i] = str[j];
		str[j] = temp;
	}
}

/**
 * string_length - Calculate the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string.
 */
int string_length(const char *str)
{
		int length = 0;

	while (str[length] != '\0')
	{
	++length;
	}
return (length);
}

