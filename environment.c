#include "eddi.h"

/**
 * set_env_variable - Set or modify an environment variable.
 * @name: The name of the environment variable.
 * @value: The value to set for the environment variable.
 * @envp: The environment variables (not used in the function).
 *
 * Return: 0 on success, -1 on failure.
 */
int set_env_variable(const char *name, const char *value, char ***envp)
{
		size_t len;
		char *env_str;
		(void)envp;

/* Create a string of the form NAME=VALUE */
len = custom_strlen(name) + custom_strlen(value) + 2; /* +2 for '=' and '\0' */
	env_str = custom_malloc(len);

	if (env_str == NULL)
	{
	perror("malloc");
	return (-1); /* Memory allocation failure */
	}

	custom_snprintf(env_str, len, "%s=%s", name, value);

/* Set the environment variable using custom_putenv */
	if (custom_putenv(env_str) != 0)
	{
	perror("putenv");
	custom_free(env_str);
	return (-1); /* Failure to set environment variable */
	}

	return (0); /* Success */
}

/**
 * unset_env_variable - Unset an environment variable.
 * @name: The name of the environment variable to unset.
 * @envp: The environment variables (not used in the function).
 *
 * Return: 0 on success, -1 on failure.
 */
int unset_env_variable(const char *name, char ***envp)
{
	(void)envp;
/* Unset the environment variable using custom_unsetenv */
	if (custom_unsetenv(name) != 0)
	{
	perror("unsetenv");
	return (-1); /* Failure to unset environment variable */
	}

	return (0); /* Success */
}

/**
 * custom_strlen - Custom implementation of the strlen function.
 * @str: Pointer to the string.
 *
 * Return: The length of the string.
 */
size_t custom_strlen(const char *str)
{
		size_t length = 0;
	while (str[length] != '\0')
	{
	length++;
}
	return (length);
}
/**
 * custom_malloc - Custom implementation of the malloc function.
 * @size: The size of the memory block to allocate.
 *
 * Return: A pointer to the allocated memory block on success, NULL on failure.
 */
void *custom_malloc(size_t size)
{
	return (malloc(size));
}

/**
 * custom_snprintf - Custom implementation of standard lib snprintf function.
 * @str: The buffer where the formatted output is stored.
 * @size: Maximum number of char to be written (including the null terminator).
 * @format: The format string that specifies the format of the output.
 *
 * Return: The number of characters that would have been written if the buffer
 * was large enough (excluding the null terminator), or a negative value
 * if an error occurred.
 */
int custom_snprintf(char *str, size_t size, const char *format, ...)
{
	int result;
	va_list args;

	va_start(args, format);
	result = custom_snprintf(str, size, format, args);
	va_end(args);

		return (result);
}
