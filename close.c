#include "eddi.h"


char *_strncpy_(char *dest, char *sou, int numz)
{
	int y;
	int z;
	char *os = dest;

	y = 0;
/*Copy characters from src to dest until n-1 characters or null-terminator*/
	while (sou[y] != '\0' && y < numz - 1)
	{
		dest[y] = sou[y];
		y++;
	}
	if (y < numz)
	{
		z = y;
	/* Fill the remaining space with null-terminators */
		while (z < numz)
		{
			dest[z] = '\0';
			z++;
		}
	}
	return os;
}


char *_strncat_(char *dest, char *sou, int numz)
{
	int y;
	int z;
	char *os = dest;

	y = 0;
	z = 0;
/* Find the end of the destination string */
	while (dest[y] != '\0')
		y++;
/*Copy characters from src to dest until n characters or null-terminator*/
	while (sou[z] != '\0' && z < numz)
	{
		dest[y] = sou[z];
		y++;
		z++;
	}
	if (z < numz)
		dest[y] = '\0';/*Ensure null-terminator is added*/
	return os;
}


char *_strchr_(char *os, char ch){

	do {
		if (*os == ch)
			return (os);
	} while (*os++ != '\0');

	return NULL;
}

