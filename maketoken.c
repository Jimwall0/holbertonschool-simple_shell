#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"
/**
 * maketoken - function that tokenizes a string based on a delimiter
 * @str: input string to be tokenized
 * @delim: the delimiter used for tokenizing
 *
 * Return: array of strings (tokens) made up from input string
 */
char **maketoken(char *str, char *delim)
{
	size_t buffsize = 256;
	char *temp = NULL;
	char **tokens = malloc(buffsize * sizeof(char *));
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
		if (strcmp(temp, "") != 0 && strcmp(temp, "\n") != 0)
			/* makes sure token is not empty or just \n */
		{
			tokens[i] = strdup(temp); /* copies tokens and places them in array */
			i++;
		}
		temp = strtok(NULL, delim); /* continues through string */
	}

	tokens[i] = NULL; /* NULL-terminate token array */
	i--; /* moves index to last valid string */

	if (i >= 0 && tokens[i][strlen(tokens[i]) - 1] == '\n')
		/* checks for \n at end of string */
	{
		tokens[i][strlen(tokens[i]) - 1] = '\0';
		/* replaces it with null terminator */
	}

	return (tokens);
}
