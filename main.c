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
	path = findpath(environ);
	pathtok = maketoken(path, ":");

	if (inputbuff == NULL)
	{
		perror("Buffer allocation failed");
		exit(1);
	}
	while (1)
	{
		ssize_t len;
		int interactive_mode = isatty(STDIN_FILENO); /* non-0 return indicates interactive */

		if (interactive_mode)
		{
			printf("$ ");
			fflush(stdout); /* print prompt immediately */
		}

		if (getline(&inputbuff, &buffsize, stdin) == -1) /* take input from stdin and stores */
			break;

		/* inputbuff[strcspn(inputbuff, "\n")] = '\0'; removes newline from input */ 
		len = strlen(inputbuff);
		if (len > 0 && inputbuff[len - 1] == '\n')
		{
			inputbuff[len - 1] = '\0';
		}

		if (strspn(inputbuff, " \t\n") == strlen(inputbuff) || inputbuff[0] == '$')
				{
				continue; 
				}

		if (interactive_mode && (strcmp(inputbuff, "exit") == 0 || feof(stdin) != 0)) /* EoF condition */
	{
			break; /* exit loop if 'exit' is entered as input */
		}

		tokens = maketoken(inputbuff, " "); /* tokenize input */

		forkandexec(pathtok, tokens);

		free_array(tokens);
	}

	free(inputbuff);
	free_array(pathtok);
	free(path);

	return (0);
}
