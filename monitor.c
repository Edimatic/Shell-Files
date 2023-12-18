#include "eddi.h"


int mult_cmd(update_p *update, char *direction)
{
	struct stat st;

	(void)update;/* Avoid unused variable warning */
	if (!direction || stat(direction, &st))
		return (0);

	if (st.st_mode & S_IFREG)/* Check if the file is a regular file */
	{
		return (1);/* It's an executable command */
	}
	return 0;/* It's not an executable command */
}


char *dupli_chars(char *direct_str, int begins, int end)
{
	static char bufa[1024];/* Static buffer to hold duplicated characters */
	int o = 0;
	int lp = 0;

	for (lp = 0, o = begins; o < end; o++)
		if (direct_str[o] != ':')
			bufa[lp++] = direct_str[o];
	bufa[lp] = 0;/* Null-terminate the duplicated characters */
	return bufa;
}

/**
 * asset_path - Finds the full path of a command in the PATH string.
 *
 * @update: The update structure
 * @direct_str: The DIRECTION string
 * @order: The order to find
 *
 * Return: The full direction of the command if found, or NULL if not found.
 */
char *asset_path(update_p *update, char *direct_str, char *order)
{
	int m = 0;
	int curr_pos = 0;
	char *lane;

	if (!direct_str)
		return (NULL);
	if ((_strlen_(order) > 2) && begin_on(order, "./"))
	{
		if (mult_cmd(update, order))
			return (order);/* The command is already a full lane */
	}
	while (1)
	{
		if (!direct_str[m] || direct_str[m] == ':')
		{
			lane = dupli_chars(direct_str, curr_pos, m);
			if (!*lane)
				_strcat_(lane, order);/* Append the command to an empty lane*/
			else
			{
				_strcat_(lane, "/");/* Append a lane separator */
				_strcat_(lane, order);/* Append a lane separator */
			}
			if (mult_cmd(update, lane))
				return lane;/* The full lane is an executable command */
			if (!direct_str[m])
				break;/* Reached the end of the DIRECTION string */
			curr_pos = m;/* Update the current position in the DIRECTION string */
		}
		m++;
	}
	return (NULL);/* The command was not found in the DIRECTION */
}

