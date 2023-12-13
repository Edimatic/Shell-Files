#include "eddi.h"


int _proexit(update_p *update)
{
	int exitcheck;

	if (update->argv[1]) /* checking to know If there is an exit arguement */
	{
		exitcheck = _erro_out(update->argv[1]);
		if (exitcheck == -1)
		{
			update->ranking = 2;
			show_error(update, "Illegal number: ");
			_funcputs(update->argv[1]);
			_funcputchar('\n');
			return 1;
		}
		update->nums_mistek = _erro_out(update->argv[1]);
		return -2;
	}
	update->nums_mistek = -1;
	return -2;
}


int _procd(update_p *update)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts_("TODO: >>getcwd failure emsg here<<\n");
	if (!update->argv[1])
	{
		dir = opt_envir(update, "HOME=");
		if (!dir)
			chdir_ret = /* TODO:Decide what this should be? */
			chdir((dir = opt_envir(update, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp_(update->argv[1], "-") == 0)
	{
		if (!opt_envir(update, "OLDPWD="))
		{
			_puts_(s);
			_putchar('\n');
			return (1);
		}
		_puts_(opt_envir(update, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: Decide what this should be */
			chdir((dir = opt_envir(update, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(update->argv[1]);
	if (chdir_ret == -1)
	{
		show_error(update, "can't cd to ");
		_funcputs(update->argv[1]), _funcputchar('\n');
	}
	else
	{
		proset_envt(update, "OLDPWD", opt_envir(update, "PWD="));
		proset_envt(update, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _prohelp - changes the current directory of the process
 * @update: Structure containing potential arguments. Used to maintain
 *		constant function prototype.
 *
 * Return: Always 0 at the end of execution
 */
int _prohelp(update_p *update)
{
	char **arg_array;

	arg_array = update->argv;
	_puts_("help call works. Function not yet implemented \n");

/* Temporary unused workaround to avoid compiler warning */
	if (0)
		_puts_(*arg_array);
	return 0;
}

