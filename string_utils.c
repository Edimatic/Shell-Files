#include "eddi.h"

/**
 * is_whitespace - Check if a character is a whitespace character.
 * @ch: The character to check.
 *
 * Return: 1 if the character is a whitespace character, 0 otherwise.
 */
int is_whitespace(char ch)
{
	return (ch == ' ' || ch == '\t' || ch == '\n' ||
		    ch == '\r' || ch == '\f' || ch == '\v');
}

/**
 * trim_whitespace - Trim leading and trailing whitespaces from a string.
 * @str: The string to trim.
 *
 * Return: Dynamically allocated string with leading & trailing whitespaces
 */
char *trim_whitespace(char *str)
{
		size_t start = 0, end = 0;
		char *trimmed_str;
		size_t i;
		size_t trimmed_len;

/* Find the start index of non-whitespace characters */
	while (is_whitespace(str[start]) && str[start] != '\0')
{
		start++;
	}
/* Find the end index of non-whitespace characters */
	while (str[end] != '\0')
{
		end++;
	}
	end--; /* Adjust to the last character before the null terminator */
	while (is_whitespace(str[end]) && end > start)
{
		end--;
	}

/* Calculate the length of the trimmed substring */
	trimmed_len = (end >= start) ? (end - start + 1) : 0;

/* Allocate memory for the trimmed string */
	trimmed_str = malloc(trimmed_len + 1);
	if (trimmed_str == NULL)
{
	perror("malloc");
	exit(EXIT_FAILURE);
}

/* Copy the trimmed substring */
	for (i = 0; i < trimmed_len; i++)
{
	trimmed_str[i] = str[start + i];
}
	trimmed_str[i] = '\0';

	return (trimmed_str);
}

