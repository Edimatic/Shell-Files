#include "eddi.h"

/**
 * hsh - Main shell loop.
 *
 * @update: Pointer to the parameter & return update struct.
 * @agtv: Argument vector from main()source.
 *
 * This function is the main loop of the shell. It repeatedly clears the
 * update structure, prompts the user for input if interactive, gets input,
 * sets update based on the input, checks for built-in commands, and if not
 * found, looks for and executes external commands.
 *
 * Return: 0 on success, 1 on error, or error code at the end.
 */
int hsh(update_p *update, char **agtv)
{
	ssize_t read_status = 0;/* Status of input reading */
	int builtin_ret = 0;/*Return value of built-in commands*/

	while (read_status != -1 && builtin_ret != -2)
	{
		remove_update(update);
		if (opt_conjoint(update))
			_puts_("$ ");
		_funcputchar(BUF_FLUSH);
		read_status = wax_input(update);
		if (read_status != -1)
		{
			make_update(update, agtv);
			builtin_ret = asset_builtin(update);
			if (builtin_ret == -1)
				asset_cmd(update);
		}
		else if (opt_conjoint(update))
			_putchar('\n');
		discharge_update(update, 0);
	}
	document_chron(update);
	discharge_update(update, 1);
	if (!opt_conjoint(update) && update->ranking)
		exit(update->ranking);
	if (builtin_ret == -2)
	{
		if (update->nums_mistek == -1)
			exit(update->ranking);
		exit(update->nums_mistek);
	}
	return builtin_ret;
}


int asset_builtin(update_p *update)
{
	int read_status;
	int builtin_pro = -1;
	builtin_submit builtinsbt[] = {
		{"exit", _proexit},
		{"env", _proenvt},
		{"help", _prohelp},
		{"history", _prohistory_},
		{"setenv", _prosetenvt},
		{"unsetenv", _prounsetenvt},
		{"cd", _procd},
		{"alias", _proalias_},
		{NULL, NULL}
	};

	for (read_status = 0; builtinsbt[read_status].dash; read_status++)
		if (strcmp(update->argv[0], builtinsbt[read_status].dash) == 0)
		{
			update->check_score++;
			builtin_pro = builtinsbt[read_status].role(update);
			break;
		}
	return builtin_pro;
}

/**
 * asset_cmd - Finds a command in PATH
 *
 * @update: Pointer to the parameter & return info structure.
 *
 * This function looks for an external command within the PATH environment
 * variable. If found, it sets the path and executes the command.
 *
 * Return: void after execution.
 */
void asset_cmd(update_p *update)
{
	char *direction = NULL;
	int y;
	int k;

	update->direct = update->argv[0];
	if (update->edgesum_up == 1)
	{
		update->check_score++;
		update->edgesum_up = 0;
	}
	for (y = 0, k = 0; update->logic[y]; y++)
		if (!opt_deli(update->logic[y], " \t\n"))
			k++;
	if (!k)
		return;

	direction = asset_path(update, opt_envir(update, "PATH="), update->argv[0]);
	if (direction)
	{
		update->direct = direction;
		furk_cmd(update);
	}
	else
	{
		if ((opt_conjoint(update) || opt_envir(update, "PATH=")
					|| update->argv[0][0] == '/') && mult_cmd(update, update->argv[0]))
			furk_cmd(update);
		else if (*(update->logic) != '\n')
		{
			update->ranking = 127;
			show_error(update, "not found\n");
		}
	}
}

/**
 * furk_cmd - Forks an exec thread to run a command.
 *
 * @update: Pointer to the parameter & return info structure.
 *
  */
void furk_cmd(update_p *update)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: Handle Errors at this point */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(update->direct, update->argv, _pro_environ(update)) == -1)
		{
			discharge_update(update, 1);
			if (errno == EACCES)
				exit(126);
			exit(-2);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(update->ranking));
		if (WIFEXITED(update->ranking))
		{
			update->ranking = WEXITSTATUS(update->ranking);
			if (update->ranking == 126)
				show_error(update, "Permission denied\n");
		}
	}
}
