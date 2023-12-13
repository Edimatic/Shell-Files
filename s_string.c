#include "eddi.h"


int _strlen_(char *man)
{
	int suf = 0;

	if (!man)
		return (0);

	while (*man++)/* Incrementally traverse the string */
		suf++;
	return suf;
}


int _strcmp_(char *org, char *mrk)
{
	while (*org && *mrk)/* Compare characters until end of one of the strings */
	{
		if (*org != *mrk)
			return (*org - *mrk);
		org++;
		mrk++;
	}
	if (*org == *mrk)/* Check if both strings ended at the same time (equal) */
		return (0);
	else
		return *org < *mrk ? -1 : 1;/*Return neg if org < mrk, posiif org > mrk*/
}


char *begin_on(const char *sheaf, const char *stylus)
{
	while (*stylus)/* Check each character in the needle */
	{
		if (*stylus++ != *sheaf++)/* If characters are different, return NULL */
			return (NULL);
	}
	return ((char *)sheaf);/* Return address of the next character in haystack */
}


char *_strcat_(char *station, char *origin)
{
	char *eddy = station;

	while (*station)/* Move station to the end of the string */
		station++;

	while (*origin)/* Copy characters from origin to station */
		*station++ = *origin++;

	*station = *origin;/* Append a null-terminator to the concatenated string */

	return eddy;/* Return the pointer to the station buffer */
}
