#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "shell.h"
/**
 * main - main function for simple shell program
 *
 * Return: 0 on successful execution of command
 */
int main(void)
{
	size_t buffsize = 1024;
	char *inputbuff = malloc(buffsize * sizeof(char));
	char *path = NULL;
	char **tokens = NULL;
	char **pathtok = NULL;
	int j = 0;

	path = findpath(environ);
	pathtok = maketoken(path, ":");

	if (inputbuff == NULL)
	{
		perror("Buffer allocation failed");
		exit(1);
	}
	while (1)
	{
		printf("$ ");
		getline(&inputbuff, &buffsize, stdin); /* take input from stdin and stores */

		printf("Input before tokenizing: %s\n", inputbuff);

		if (feof(stdin) != 0) /* checks for EoF condition */
			break;

		inputbuff[strcspn(inputbuff, "\n")] = '\0'; /* removes newline from input */

		if (strcmp(inputbuff, "exit") == 0)
		{
			break; /* exit loop if 'exit' is entered as input */
		}

		tokens = maketoken(inputbuff, " "); /* tokenize input */

		while (tokens[j] != NULL)
		{
			printf("Token %d: %s\n", j, tokens[j]);
			j++;
		}

		forkandexec(pathtok, tokens);
	}

	free(inputbuff);
	free_array(pathtok);

	return (0);
}
