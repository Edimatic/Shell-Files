
#include "eddi.h"

 
char *get_chron_doc(update_p *update)
{
	char *bufa;
	char *direct;

	direct = opt_envir(update, "HOME=");/*Get user's home directory*/
	if (!direct)
		return (NULL);
	bufa = malloc(sizeof(char) * (_strlen_(direct) + _strlen_(HIST_FILE) + 2));
	if (!bufa)
		return (NULL);
	bufa[0] = 0;
	_strcpy_(bufa, direct);
	_strcat_(bufa, "/");
	_strcat_(bufa, HIST_FILE);/*Concatenate home dir path with history file name*/
	return bufa;
}

/**
 * document_chron - Writes history entries to a file.
 *
 * @update: Pointer to the info_t struct containing history information.
 *
 * Return: 1 on success, -1 on failure.
 */
int document_chron(update_p *update)
{
	ssize_t fildes;
	char *box_name = get_chron_doc(update);
	regis_t *node = NULL;

	if (!box_name)
		return (-1);

	fildes = open(box_name, O_CREAT | O_TRUNC | O_RDWR, 0644);/*Open history fil*/
	free(box_name);
	if (fildes == -1)
		return (-1);
	for (node = update->history; node; node = node->after)/*Writ history entries*/
	{
		_puts_fildes(node->rop, fildes);
		_putfildes('\n', fildes);
	}
	_putfildes(BUF_FLUSH, fildes);/*Flush the output buffer*/
	close(fildes);
	return (1);
}

/**
 * present_chron - present chronicle entries from a file.
 *
 * @update: Pointer to the update_p struct containing history information.
 *
 */
int present_chron(update_p *update)
{
	int gh, last = 0;
	int rulecount = 0;
	ssize_t fildes, read_lengt;
	ssize_t fsize = 0;
	struct stat st;
	char *bufa = NULL, *box_name = get_chron_doc(update);

	if (!box_name)
		return 0;

	fildes = open(box_name, O_RDONLY);/*OPen chronicle file for reading*/
	free(box_name); 
	if (fildes == -1)
		return (0);
	if (!fstat(fildes, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	bufa = malloc(sizeof(char) * (fsize + 1));/*Allocate bufa for reading*/
	if (!bufa)
		return 0;
	read_lengt = read(fildes, bufa, fsize);/*Read file into bufa*/
	bufa[fsize] = 0;
	if (read_lengt <= 0)
		return (free(bufa), 0);
	close(fildes);
	for (gh = 0; gh < fsize; gh++)/*Parse & build history list from read bufa*/
		if (bufa[gh] == '\n')
		{
			bufa[gh] = 0;
			produce_chron_reg(update, bufa + last, rulecount++);
			last = gh + 1;
		}
	if (last != gh)
		produce_chron_reg(update, bufa + last, rulecount++);
	free(bufa);
	update->pass_note = rulecount;
	while (update->pass_note-- >= HIST_MAX)/*Trim hist list if exceeds max*/
		remov_node_via_roll(&(update->history), 0);
	renums_chron(update);/*Renumber the history list*/
	return (update->pass_note); }



int produce_chron_reg(update_p *update, char *bufa, int cordcount)
{
	regis_t *node = NULL;

	if (update->history)
		node = update->history;
	attach_node_end(&node, bufa, cordcount);

	if (!update->history)
		update->history = node;
	return (0);
}

/**
 * renums_chron - When chenage is complete renumber the chronicle link list.
 *
 * @update: Pointer to the update_p struct containing history information.
 *
 * Return: The new histcount (number of history entries).
 */
int renums_chron(update_p *update)
{
	regis_t *node = update->history;
	int gh = 0;

	while (node)
	{
		node->figure = gh++;
		node = node->after;
	}
	return (update->pass_note = gh);
}
