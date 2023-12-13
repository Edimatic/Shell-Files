#include "eddi.h"


char **strtop_k(char *ztg, char *d_ter)
{
	int x, y;
	int kim, min;
	int numz = 0;
	char **words;

	if (ztg == NULL || ztg[0] == 0)
		return (NULL);
	if (!d_ter)/*if delim r not provided, use a space*/
		d_ter = " ";
	for (x = 0; ztg[x] != '\0'; x++)/*count the nums of words*/
		if (!opt_deli(ztg[x], d_ter) && (opt_deli(ztg[x + 1], d_ter) || !ztg[x + 1]))
			numz++;

	if (numz == 0)/*If no words found, return NULL*/
		return (NULL);
	words = malloc((1 + numz) * sizeof(char *));/*Allocate memory for array*/
	if (!words)
		return NULL;
	for (x = 0, y = 0; y < numz; y++)/*Split the input string into words*/
	{
		while (opt_deli(ztg[x], d_ter))/*Skip leading delimiters*/
			x++;
		kim = 0;
		while (!opt_deli(ztg[x + kim], d_ter) && ztg[x + kim])/*Extraction*/
			kim++;
		words[y] = malloc((kim + 1) * sizeof(char));/*Allocate memory*/
		if (!words[y])
		{
			for (kim = 0; kim < y; kim++)/*Free prwviously allocated memory*/
				free(words[kim]);
			free(words);
			return NULL;
		}
		for (min = 0; min < kim; min++)/*Copy the word into array*/
			words[y][min] = ztg[x++];
		words[y][min] = 0;
	}
	words[y] = NULL;/*Set the lasr element of the array to NULL*/
	return words;
}

/**
 * **strto_k - Split a string into words based on a single delimiter character.
 *
 * @ztg: The input string loaded.
 * @d_ter: the delimeter character loaded.
 *
 * Return: a pointer to an array of strings, or NULL if fail.
 */
char **strto_k(char *ztg, char d_ter)
{
	int i, j;
	int kim, min;
	int nums = 0;
	char **words;

	if (ztg == NULL || ztg[0] == 0)
		return (NULL);
	for (i = 0; ztg[i] != '\0'; i++)/*Count the num of words in the inputstring*/
		if ((ztg[i] != d_ter && ztg[i + 1] == d_ter) ||
				    (ztg[i] != d_ter && !ztg[i + 1]) || ztg[i + 1] == d_ter)
			nums++;
	if (nums == 0)/*If no words found, return NULL*/
		return (NULL);
	words = malloc((1 + nums) * sizeof(char *));/*Allocate memory for array*/
	if (!words)
		return NULL;
	for (i = 0, j = 0; j < nums; j++)/*Split the input string into words*/
	{
		while (ztg[i] == d_ter && ztg[i] != d_ter)/*Skip leading delim*/
			i++;
		kim = 0;
		while (ztg[i + kim] != d_ter && ztg[i + kim] && ztg[i + kim] != d_ter)
			kim++;
		words[j] = malloc((kim + 1) * sizeof(char));/*Allocate memory for word*/
		if (!words[j])
		{
			for (kim = 0; kim < j; kim++)/*Free previously allocated*/
				free(words[kim]);
			free(words);
			return (NULL);
		}
		for (min = 0; min < kim; min++)/*Copy the word into the array*/
			words[j][min] = ztg[i++];
		words[j][min] = 0;
	}
	words[j] = NULL;/*Set the last element of the array to NULL*/
	return words;
}
