#include "eddi.h"

/**
 * custom_fprintf_stderr - Custom implementation of fprintf to stderr.
 * @format: The format string.
 * @...: The additional arguments for formatting.
 */
void custom_fprintf_stderr(const char *format, ...)
{
	va_list args;
	char buffer[1024]; /* Adjust the buffer size as needed */

	va_start(args, format);
	vsnprintf(buffer, sizeof(buffer), format, args);

	va_end(args);

/* Use write to print to stderr */
		write(2, buffer, custom_strlen(buffer));
}

/**
 * custom_getenv - Custom implementation of getenv function.
 * @name: The name of the environment variable.
 * @envp: The environment variables.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *custom_getenv(const char *name, char **envp)
{
/* Iterate through envp to find the environment variable */
	while (*envp != NULL)
	{
		char *current_env = *envp;

	if (custom_strcmp(current_env, name) == 0)
	{
/* If the variable is found, return its value */
	char *value = current_env + custom_strlen(name) + 1;

	return (value);
	}
		envp++;
	}

/* Return NULL if the variable is not found */
	return (NULL);
}

/**
 * custom_strcmp - Custom implementation of strcmp function.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: 0 if strings are equal, positive if s1 > s2, negative if s1 < s2.
 */
int custom_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * custom_getcwd - Custom implementation of getcwd function.
 * @buf: The buffer to store the current working directory.
 * @size: The size of the buffer.
 *
 * Return: If successful, returns buf; otherwise, returns NULL.
 */
char *custom_getcwd(char *buf, size_t size)
{
	if (buf == NULL)
	{
	/* Allocate memory for the buffer if not provided */
	buf = (char *)malloc(size);
	if (buf == NULL)
	{
	/* Memory allocation failure */
		return (NULL);
}
	}

	if (getcwd(buf, size) == NULL)
	{
/* Failure to get the current working directory */
		return (NULL);
}

		return (buf);
}

