#include "eddi.h"


int _prohistory_(update_p *update)
{
	/*Display the history list using the print_list function */
	output_register(update->history);
	return (0);
}


int unmake_alias_(update_p *update, char *str)
{
	char *b;
	char w;
	int ret;

/* Find the equal sign in the alias string */
	b = _strchr_(str, '=');
	if (!b)
		return (1);

/* Temporarily replace the equal sign with null terminator */
	w = *b;
	*b = 0;

/* Delete the alias node from the linked list */
	ret = remov_node_via_roll(&(update->alias),
	bring_node_roll(update->alias, node_begin_on(update->alias, str, -1)));

/* Restore the equal sign */
	*b = w;
	return (ret);
}


int make_alias_(update_p *update, char *str)
{
	char *b;

/* Find the equal sign in the alias string */
	b = _strchr_(str, '=');
	if (!b)
		return (1);

/* If alias value is empty, unset the alias */
	if (!*++b)
		return (unmake_alias_(update, str));

/* Unset existing alias and add new alias to linked list */
	unmake_alias_(update, str);
	return (attach_node_end(&(update->alias), str, 0) == NULL);
}


int show_alias_(regis_t *node)
{
	char *b = NULL, *v = NULL;

	if (node)
	{
/* Find the equal sign in the alias node's string */
		b = _strchr_(node->rop, '=');

/* Print the alias name followed by '=' and enclosed value in single quotes*/
		for (v = node->rop; v <= b; v++)
		_putchar(*v);
		_putchar('\'');
		_puts_(b + 1);
		_puts_("'\n");
		return (0);
	}
	return 1;
}


int _proalias_(update_p *update)
{
	int m = 0;
	char *b = NULL;
	regis_t *node = NULL;

	if (update->argc == 1)
	{
/* If no arguments provided, print all aliases */
		node = update->alias;
		while (node)
		{
			show_alias_(node);
			node = node->after;
		}
		return (0);
	}

/* Loop through provided arguments to set or print aliases */
	for (m = 1; update->argv[m]; m++)
	{
		b = _strchr_(update->argv[m], '=');
		if (b)
			make_alias_(update, update->argv[m]);
		else
		show_alias_(node_begin_on(update->alias, update->argv[m], '='));
	}

	return (0);
}

