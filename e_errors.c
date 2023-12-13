#include "eddi.h"

/**
 * _erro_out - converts a string to an integer.
 *
 * @stg: the string to be converted
 *
 * Return: The converted number if successful, -1 on error.
 */
int _erro_out(char *stg)
{
	int h = 0;
	unsigned long int output = 0;

	if (*stg == '+')
		stg++;  /* Skip leading '+' sign */

/*Iterate through the string and convert characters to an integer*/
	for (h = 0;  stg[h] != '\0'; h++)
	{
		if (stg[h] >= '0' && stg[h] <= '9')
		{
			output *= 10;
			output += (stg[h] - '0');
			if (output > INT_MAX)
				return (-1);/* Overflow */
		}
		else
			return (-1);/* Non-numeric character encountered */
	}
	return output;
}


void show_error(update_p *update, char *estr)
{
	_funcputs(update->file_tag);
	_funcputs(": ");
	show_dir(update->check_score, STDERR_FILENO);
	_funcputs(": ");
	_funcputs(update->argv[0]);
	_funcputs(": ");
	_funcputs(estr);
}

/**
 * show_dir - Prints a decimal (integer) number (base 10).
 *
 * @typein: The input number to be printed.
 * @fildes: The file descriptor which to be written.
 *
 * Return: Number of characters printed.
 */
int show_dir(int typein, int fildes)
{
	int (*__putchar)(char) = _putchar;
	int m, count = 0;
	unsigned int _abs_, current;

	if (fildes == STDERR_FILENO)
		__putchar = _funcputchar;

/* Handle negetive numbers */
	if (typein < 0)
	{
		_abs_ = -typein;
		__putchar('-');
		count++;
	}
	else
		_abs_ = typein;
	current = _abs_;
	for (m = 1000000000; m > 1; m /= 10)
	{
		if (_abs_ / m)
		{
			__putchar('0' + current / m);
			count++;
		}
		current %= m;
	}
	__putchar('0' + current);
	count++;

	return count;
}

/**
 * change_numz - Converts a number to a string with a given base.
 *
 * @no:Number to be converted.
 * @bez: Base for conversion.
 * @flag: Argument flags
 *
    
 */
char *change_numz(long int no, int bez, int flag)
{
	static char *arr;
	static char bufa[50];
	char sign = 0;
	char *pt;
	unsigned long n = no;

	/* Handle signed numbers */
	if (!(flag & CONVERT_UNSIGNED) && no < 0)
	{
		n = -no;
		sign = '-';

	}
	arr = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pt = &bufa[49];
	*pt = '\0';

/* Convert the number to the specified bez */
	do	{
		*--pt = arr[n % bez];
		n /= bez;
	} while (n != 0);

	if (sign)
		*--pt = sign;
	return pt;
}

/**
 * take_out_comments - Replaces the first instance of '#' with '\0'.
 *
 * @buf: Address of the string to modify
 *
 * Return: None after execution.
 */
void take_out_comments(char *buf)
{
	int c;

/* Find the first instance of '#' and replace it with '\0' */
	for (c = 0; buf[c] != '\0'; c++)
	{
		if (buf[c] == '#' && (!c || buf[c - 1] == ' '))
		{
			buf[c] = '\0';
			break;
		}
	}
}

