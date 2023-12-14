#include "shell.h"
/**
 *  * custom_strcat - Custom implementation of strcat.
 *   * @dest: The destination string.
 *    * @src: The source string.
 */
void custom_strcat(char *dest, const char *src)
{
while (*dest)
dest++;
while ((*dest++ = *src++))
;
}
