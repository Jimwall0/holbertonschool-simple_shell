#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"

char **maketoken(char *str, char *delim)
{
	size_t buffsize = 256;
	char *temp = NULL;
	char **tokens = malloc(buffsize * sizeof(char *));
	int cmpval;
	int i = 0;

	if (str == NULL)
	{
		perror("Error: input string NULL");
		exit(1);
	}
	if (tokens == NULL)
	{
		perror("Error: memory allocation failed");
		exit(1);
	}

	temp = strtok(str, delim);
	while (temp != NULL)
	{
		cmpval = strcmp(temp, "\n"); /* checks to see if token is \n */
		if (cmpval == 0) /* returns 0 if \n */
			break;

		tokens[i] = strdup(temp); /* copies tokens and places them in tokens array */
		temp = strtok(NULL, delim); /* continues through string */
		i++;
	}

	tokens[i] = NULL; /* NULL-terminate token array */
	i--; /* moves index to last valid string */

	if (i >= 0 && tokens[i][strlen(tokens[i]) - 1] == '\n') /* checks for \n at end of string */
		tokens[i][strlen(tokens[i]) - 1] = '\0'; /* replaces it with null terminator */
	
	return(tokens);
}
