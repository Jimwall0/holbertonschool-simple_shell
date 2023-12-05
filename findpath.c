#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *find_executable(const char *command, char *env[])
{
	char *path_var = NULL;
	char *path_copy;
	char *dir;
	char full_path[MAX_PATH_LEN];
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			/* checks first 5 characters for match */
		{
		path_var = env[i] + 5; /* Skip "PATH=" */
		break;
		}
	}
	if (path_var == NULL)
	{
		fprintf(stderr, "Error: PATH variable not set.\n");
		return (NULL);
	}
	path_copy = strdup(path_var);
	/* creates copy of path var that can be manipulated */
	if (path_copy == NULL)
	{
		perror("Error");
		return (NULL);
	}
	dir = strtok(path_copy, ":");
	/* splits path into individual directories */
	while (dir != NULL)
	{
		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, command);
		/* builds full path by combining directory and command */
		if (access(full_path, X_OK) == 0)
			/* checks if file is executable */
		{
			free(path_copy);
			return (strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
