#include "eddi.h"

/**
 * load_bufa - Reads and buffers chained commands.
 *
 * @update: The parameter struct containing shell information.
 * @bufa: Address of the buffer to store the input.
 * @distance: Address of the length variable for the buffer.
 *
 * Return: Number of bytes read.
 */
ssize_t load_bufa(update_p *update, char **bufa, size_t *distance)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*distance) /* If buffer is empty, read and fill it */
	{
		free(*bufa);/* Free previous buffer */
		*bufa = NULL;
		signal(SIGINT, sigl_Handler);/* Handle Ctrl-C */
#if USE_GETLINE
		r = wax_getline(bufa, &len_p, stdin);/* Read line */
#else
		r = wax_get_line(update, bufa, &len_p);
#endif
		if (r > 0)
		{
		if ((*bufa)[r - 1] == '\n')
			{
		(*bufa)[r - 1] = '\0'; /* delete trailing newline */
				r--;
			}
	update->edgesum_up = 1;
	take_out_comments(*bufa);/* Take out comments from the input */
	produce_chron_reg(update, *bufa, update->pass_note++);/* Add to history */

			{
			*distance = r;
			update->grip_bufa = bufa;/* Store command chain buffer */
			}
		}
	}
	return r;
}


ssize_t wax_input(update_p *update)
{
	static char *buf; /* command chain buffa */
	static size_t q;
	static size_t j, len;
	ssize_t x = 0;
	char **buf_p = &(update->logic), *p;

	_putchar(BUF_FLUSH);/* Flush buffer */
	x = load_bufa(update, &buf, &len);
	if (x == -1) /* if EOF */
		return (-1);
	if (len) /* If there are commands in the chain buffer */
	{
		j = q;
		p = buf + q;

		confi_chan(update, buf, &j, q, len);/* Check for command chain */
		while (j < len) /* Iterate to semicolon or end process */
		{
			if (pro_chan(update, buf, &j))
				break;
			j++;
		}

		q = j + 1; /* Increment past nulled */
		if (q >= len) /* Reached end of buffa? */
		{
			q = len = 0; /* Reset position & len */
			update->grip_bufa_dash = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen_(p));
	}

	*buf_p = buf; /* not a chain, pass back buffer */
	return x; /* return length of buffa*/
}

/**
 * scan_bufa - Reads input into the given buffa.
 *
 * @update: The parameter struct containing shell information.
 * @bufa: The buffa
 * @index: The size
 *
 * Return: Number of bytes ready to be read.
 */
ssize_t scan_bufa(update_p *update, char *bufa, size_t *index)
{
	ssize_t q = 0;

	if (*index)
		return (0);
	q = read(update->fildes_output, bufa, READ_BUF_SIZE);/* Read into buffer */
	if (q >= 0)
		*index = q;
	return q;
}

/**
 * wax_get_line - Reads a line of input from STANDARD INPUT.
 *
 * @update: The parameter struct containing shell information.
 * @pot: Address of the pointer to buffer (preallocated or NULL)
 * @distance: Size of the preallocated buffer if not NULL.
 *
 * Return: Number of bytes read.
 */
int wax_get_line(update_p *update, char **pot, size_t *distance)
{
	static char buf[READ_BUF_SIZE];
	static size_t i;
	static size_t len;
	size_t k;
	ssize_t r = 0, os = 0;
	char *pal = NULL, *old_opp = NULL;
	char *ch;

	pal = *pot;
	if (pal && distance)
		os = *distance;
	if (i == len)
		i = len = 0;

	r = scan_bufa(update, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	ch = strchr(buf + i, '\n');
	k = ch ? 1 + (unsigned int)(ch - buf) : len;
	old_opp = _allocate(pal, os, os ? os + k : k + 1);
	if (!old_opp) /* MALLOC FAILURE! */
		return (pal ? free(pal), -1 : -1);

	if (os)
		strncat(old_opp, buf + i, k - i);/* Concatenate new data */
	else
		strncpy(old_opp, buf + i, k - i + 1);

	os += k - i;
	i = k;
	pal = old_opp;

	if (distance)
		*distance = os;
	*pot = pal;
	return os;
}

/**
 * sigl_Handler - Handles Ctrl-C signal.
 * @sig_num: The signal number
 *
 * Return: void after execution
 */
void sigl_Handler(__attribute__((unused))int sig_num)
{
	printf("\n");/* Print newline */
	printf("$ ");/* Print prompt */
	_putchar(BUF_FLUSH);
}

