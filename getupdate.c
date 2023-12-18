#include "eddi.h"

/**
 * remove_update - Initializes an update_p structure by resetting its fields.
 *
 * @update: Pointer to the update_p struct to be cleared.
 */
void remove_update(update_p *update)
{
	update->logic = NULL;
	update->argv = NULL;
	update->direct = NULL;
	update->argc = 0;
}


void make_update(update_p *update, char **him)
{
	int g = 0;

	update->file_tag = him[0];/* Set the program's filename */
	if (update->logic)
	{
	update->argv = strtop_k(update->logic, " \t");/* Tokenize argument string */
			if (!update->argv)
		{
	/* Allocate space for argv array */
			update->argv = malloc(sizeof(char *) * 2);
	if (update->argv)
			{
	update->argv[0] = _strdup_(update->logic);/* Copy argument to argv */
				update->argv[1] = NULL;
			}
		}
		for (g = 0; update->argv && update->argv[g]; g++)/* Count argc */
			;
		update->argc = g;

		reassign_alias(update);/* Reassign aliases in argv */
		reassign_vars(update);/* Reassign environ variable references in argv */
	}
}

/**
 * discharge_update - Frees memory associated with an update_p struct's fields.
 *
 * @update: Pointer to the update_p struct to be freed.
 *
        
 */
void discharge_update(update_p *update, int hal)
{
	f_empty(update->argv);/* Free the argv array */
	update->argv = NULL;
	update->direct = NULL;
	if (hal)
	{
		if (!update->grip_bufa)
	/* Free argument string if not part of a command chain */
			free(update->logic);
	 	if (update->env)
			empty_register(&(update->env));/* Free environment linked list */
		if (update->history)
			empty_register(&(update->history));/* Free history linked list */
		if (update->alias)
			empty_register(&(update->alias));/* Free alias linked list */
		f_empty(update->environ);/* Free environment string array */
			update->environ = NULL;
		pro_free((void **)update->grip_bufa);/* Free command buffer */
		if (update->fildes_output > 2)
			close(update->fildes_output);/* Close file descriptor */
		_putchar(BUF_FLUSH);/* Flush the output buffer */
	}
}
