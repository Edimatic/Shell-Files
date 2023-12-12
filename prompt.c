#include "eddi.h"

/**
 * display_prompt - Display a prompt for the user to enter a command.
 */
void display_prompt(void)
{
	const char prompt[] = "$ "; /*prompt message */

	write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);

	fflush(stdout);
}

/**
 * custom_strcpy - Custom implementation of strcpy function.
 * @dest: The destination buffer.
 * @src: The source string to copy.
 *
 * Return: A pointer to the destination buffer.
 */
char *custom_strcpy(char *dest, const char *src)
{
	char *original_dest = dest;

	while ((*dest++ = *src++) != '\0')
	{
 /* Copy characters from src to dest until null terminator is encountered*/
	}

		return (original_dest);
}

/**
* snprintf_custom - Custom implementation of the snprintf function.
* @str: The buffer where the formatted output is stored.
* @size: Maximum num of char to be written (including the null terminato    r).
* @format: The format string that specifies the format of the output.
*
* Return: The number of characters written (excluding the null terminator)
* if the entire formatted string fits within the provided buffer;
* otherwise, the total number of characters that would have been written
* if enough space were available (excluding the null terminator).
*/
int snprintf_custom(char *str, size_t size, const char *format, ...)
{
		va_list args;
		int ret;

	va_start(args, format);
	ret = vsnprintf(str, size, format, args);
	va_end(args);

		return (ret);
}

