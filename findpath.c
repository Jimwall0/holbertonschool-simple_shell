#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"
/**
 * findpath - function that finds / copies path variable
 * @env: array of strings representing environment vars
 * Return: PATH string, or NULL if not found
 */
char *findpath(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			return (strdup(env[i] + 5));
		}
		i++;
	}

	return (0);
}
