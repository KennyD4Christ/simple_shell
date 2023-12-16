#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@num: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int num)
{
	unsigned int x;

	for (x = 0; x < num; x++)
		s[x] = b;
	return (s);
}

/**
 * forkfree - frees a string of strings
 * @ppt: string of strings
 */
void forkfree(char **ppt)
{
	char **b = ppt;

	if (!ppt)
		return;
	while (*ppt)
		free(*ppt++);
	free(b);
}

/**
 * _relock - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_sz: byte size of previous block
 * @new_sz: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_relock(void *ptr, unsigned int old_sz, unsigned int new_sz)
{
	char *p;

	if (!ptr)
		return (malloc(new_sz));
	if (!new_sz)
		return (free(ptr), NULL);
	if (new_sz == old_sz)
		return (ptr);

	p = malloc(new_sz);
	if (!p)
		return (NULL);

	old_sz = old_sz < new_sz ? old_sz : new_sz;
	while (old_sz--)
		p[old_sz] = ((char *)ptr)[old_sz];
	free(ptr);
	return (p);
}
