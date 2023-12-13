#include "eddi.h"

/**
 * main - The entry point of the shell program.
 *
 * @argct: Argument count to the condition.
 * @argvt: Argument vector to the condition.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int argct, char **argvt)
{
	update_p update[] = { UPDATE_INIT };/* Initialize an update_p structure */
	int fd = 2;

/* Inline assembly to perform some operation on 'fildes'*/
	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (argct == 2)
	{
		fd = open(argvt[1], O_RDONLY);/* Attempt to open a file for reading */
		if (fd == -1)
		{
			if (errno == EACCES)
				/*exit(126);// Exit with code 126 on permission denied*/
			if (errno == ENOENT)
			{
				_funcputs(argvt[0]);
				_funcputs(": 0: Can't open ");
				_funcputs(argvt[1]);
				_funcputchar('\n');/* Print an error message */
				_funcputchar(BUF_FLUSH);
				/*exit(127) Exit with code 127 if file not found */
			}
			return (EXIT_FAILURE);/* Return failure code for other errors */
		}
		update->fildes_output = fd;/* Set the 'fildes' field in the 'update' struct*/
	}
	pop_envt_regis(update);/* Populate the envt list in the 'update' structure*/
	present_chron(update);/* Read command history from a file */
	hsh(update, argvt);/* Start the shell's main loop */
	return (EXIT_SUCCESS);/* Return success code */
}

