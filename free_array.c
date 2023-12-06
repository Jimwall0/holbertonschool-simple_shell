#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
/**
 * free_array - function that frees string array memory
 * @array: array of strings to be freed
 */

void free_array(char **array)
{
	int i = 0;

	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
