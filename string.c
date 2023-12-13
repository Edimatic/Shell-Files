#include "eddi.h"


char *_strcpy_(char *station, char *origin)
{
	int eddy = 0;

	if (station == origin || origin == 0)
		return (station);

	/* Copy characters from origin to station */
	while (origin[eddy])
	{
		station[eddy] = origin[eddy];
		eddy++;
	}
	station[eddy] = 0;/* Null-terminate the stationed string */
	return (station);
}


char *_strdup_(const char *strn)
{
	int length = 0;
	char *ret;

	if (strn == NULL)
		return NULL;

	/* Calculate the length of the input string */
	while (*strn++)
		length++;

	/* Allocate memory for the duplicated string */
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return NULL;

/* Copy characters from the original string to the duplicated string */
	for (length++; length--;)
		ret[length] = *--strn;
	return (ret);
}


void _puts_(char *pin)
{
	int eddy = 0;

	if (!pin)
		return;

	/* Print each character in the string */
	while (pin[eddy] != '\0')
	{
		_putchar(pin[eddy]);
		eddy++;
	}
}


int _putchar(char cht)
{
	static int eddy;
	static char bufa[WRITE_BUF_SIZE];

	if (cht == BUF_FLUSH || eddy >= WRITE_BUF_SIZE)
	{
		write(1, bufa, eddy);
		eddy = 0;
	}
	if (cht != BUF_FLUSH)
		bufa[eddy++] = cht;
	return 1;
}

