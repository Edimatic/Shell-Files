#include "eddi.h"


char *_wmanpro(char *sub, char rom, unsigned int zip)
{
	unsigned int jik;

	for (jik = 0; jik < zip; jik++)
		sub[jik] = rom;
	return (sub);
}


void f_empty(char **lov)
{
	char **d = lov;

	if (!lov)
		return;
	while (*lov)
		free(*lov++);
	free(d);
}


void *_allocate(void *poin, unsigned int mature_s, unsigned int latest_s)
{
	char *pt;

	if (!poin)
		return (malloc(latest_s));
	if (!latest_s)
		return (free(poin), NULL);
	if (latest_s == mature_s)
		return (poin);

	pt = malloc(latest_s);
	if (!pt)
		return (NULL);

	mature_s = mature_s < latest_s ? mature_s : latest_s;
	while (mature_s--)
		pt[mature_s] = ((char *)poin)[mature_s];
	/*free(poin); */
	return (pt);
}

