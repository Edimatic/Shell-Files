#include "eddi.h"

/**
 * _proenvt - prints the current environment
 *
 * @update: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 * Return: Always 0 after execution
 */
int _proenvt(update_p *update)
{

/* Print the environment list using the print_list_str function */
	output_reg_strn(update->env);
	return 0;
}


char *opt_envir(update_p *update, const char *label)
{
	regis_t *node = update->env;
	char *b;

	while (node)
	{
/* Check if the node's string starts with the given name */
		b = begin_on(node->rop, label);
		if (b && *b)
			return (b);
		node = node->after;
	}
	return NULL;
}

/**
 * _prosetenvt - Initialize a new envt variable,if not modify the current one.
 *
 * 
 *
 *  Return: Always 0 after execution
 */
int _prosetenvt(update_p *update)
{
	if (update->argc != 3)
	{
		_funcputs("Incorrect number of arguements\n");
		return (1);
	}

	/* Set or modify the environment variable using the _setenv function */
	if (proset_envt(update, update->argv[1], update->argv[2]))
		return (0);
	return 1;
}


int _prounsetenvt(update_p *update)
{
	int v;

	if (update->argc == 1)
	{
		_funcputs("Too few arguements.\n");
		return (1);
	}
/* Loop through provided arguments and unset environment variables */
	for (v = 1; v <= update->argc; v++)
		_pro_unsetenvt(update, update->argv[v]);

	return (0);
}

/**
 * pop_envt_regis - populates envt linked list of the file.
 *
 * 
 * Return: Always 0 after execution.
 */
int pop_envt_regis(update_p *update)
{
	regis_t *node = NULL;
	size_t m;

	/* Populate the environment linked list using the environ array */
	for (m = 0; environ[m]; m++)
		attach_node_end(&node, environ[m], 0);
	update->env = node;
	return 0;
}

