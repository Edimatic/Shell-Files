#include "eddi.h"

/**
 * pro_free - Frees a pointer and sets it to NULL.
 *
 * @pot: Address of the pointer to be freed.
 *
 *This function frees the memory pointed to by the given pointer and
 *then sets the pointer itself to NULL to avoid any potential
 *use-after-free issues.
 *
 * 
 */
int pro_free(void **pot)
{
	if (pot && *pot)
	{
		free(*pot);/* Free the memory pointed to by 'ptr' */
		*pot = NULL;/* Set 'ptr' to NULL to prevent further use */
		return (1);/* Return 1 to indicate successful memory freeing */
	}
	return 0;/* Return 0 if 'ptr' was already NULL or invalid */
}

