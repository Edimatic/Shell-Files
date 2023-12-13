#include "eddi.h"

/**
 * _pro_environ - Returns the actual copy of environment string array
 *
 *  Pointer to the array of environment strings.
 */
char **_pro_environ(update_p *update)
{
if (!update->environ || update->pro_envt)
	{

/* Convert linked list to string array */
	update->environ = register_via_strn(update->env);
	update->pro_envt = 0;
	}

	return update->environ;
}

/**
 * _pro_unsetenvt - Remove an environment variable
 *
 * @varia: The string representing the environment variable
 *
 *  Return: 1 on successful delete, 0 otherwise
 */
int _pro_unsetenvt(update_p *update, char *varia)
{
	regis_t *node = update->env;
	size_t q = 0;
	char *pik;

	if (!node || !varia)
		return 0; 

	while (node)
	{
		pik = begin_on(node->rop, varia);
		if (pik && *pik == '=')
		{
		update->pro_envt = remov_node_via_roll(&(update->env), q);
			q = 0;
			node = update->env;
			continue;
		}
		node = node->after;
		q++;
	}
	return (update->pro_envt);
}

/**
 * proset_envt - Initialize a new environment variable,
 *             or modify an existing one
 * @update: Structure containing potential arguments. Used to maintain
 *        constant prototype.
 * @varia: The string representing the environment variable.
 * @va: The string representing the environment variable's value.
 *
 *  Return: Always 0 after execution
 */
int proset_envt(update_p *update, char *varia, char *va)
{
	char *bufa = NULL;
	regis_t *node;
	char *pik;

	if (!varia || !va)
		return (0);
/* Allocate memory for var=value pair */
	bufa = malloc(_strlen_(varia) + _strlen_(va) + 2);
	if (!bufa)
		return (1);
	_strcpy_(bufa, varia);/* Copy variable name to buffer */
	_strcat_(bufa, "=");/* Append '=' */
	_strcat_(bufa, va);/* Append value */
	node = update->env;

/* Check if variable exists; if yes, update its value; if not, add new entry */
	while (node)
	{
		pik = begin_on(node->rop, varia);
		if (pik && *pik == '=')
		{
			free(node->rop);
			node->rop = bufa;
			update->pro_envt = 1;
			return (0);
		}
		node = node->after;
	}
	attach_node_end(&(update->env), bufa, 0);/* Add new entry to linked list */
	free(bufa);
	update->pro_envt = 1;
	return 0;
}
