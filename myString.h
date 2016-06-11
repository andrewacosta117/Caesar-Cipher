#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

char *myString(void)
{
	char *buffer = NULL;
	unsigned int cap = 0;
	unsigned int n = 0;
	int c;
	
	while ((c = fgetc(stdin)) != '\n' && c != EOF)
	{
		if (n + 1 > cap)
		{
			if (cap == 0)
			{
				cap = 32;
			}
			else if (cap <= (UINT_MAX /2))
			{
				cap *= 2;
			}
			else
			{
				free(buffer);
				return NULL;
			}
			
			char *temp = realloc(buffer, cap * sizeof(char));
			if (temp == NULL)
			{
				free(buffer);
				return NULL;
			}
			buffer = temp;
		}
		buffer[n++] = c;
	}
	if (n == 0 && c == EOF)
	{
		return NULL;
	}
	char *minimal = malloc ((n + 1) * sizeof(char));
	strncpy(minimal, buffer, n);
	free(buffer);
	
	minimal[n] = '\0';
	
	return minimal;
}
#endif