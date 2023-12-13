#include "eddi.h"


int opt_conjoint(update_p *update)
{
/*Check if standard input is a terminal & readfd is within the valid range*/
	return (isatty(STDIN_FILENO) && update->fildes_output <= 2);
}


int opt_deli(char kai, char *delimiter)
{
	while (*delimiter)
	{
/* Compare the character with each character in the delimiter string */
		if (*delimiter++ == kai)
			return (1);
	}
		return (0);
}



int opt_alphabet(int chr)
{
	if ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z'))
		return (1);
	else
		return (0);
}


int opt_atoi(char *sim)
{
	int k;
	int sign = 1;
	int flag = 0, output;
	unsigned int result = 0;

	for (k = 0; sim[k] != '\0' && flag != 2; k++)
	{
	/* Handle the sign of the number */
		if (sim[k] == '-')
			sign *= -1;

		if (sim[k] >= '0' && sim[k] <= '9')
		{
	/* Convert character to integer and build the result */
			flag = 1;
			result *= 10;
			result += (sim[k] - '0');
		}
		else if (flag == 1)
		flag = 2;/* Stop parsing after encountering digits*/

/*The loop continue until either the end of string or 2 consecutive non-digit*/

	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

