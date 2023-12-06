#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

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
