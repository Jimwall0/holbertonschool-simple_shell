#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
/**
 * forkandexec - function that forks CID and executes command
 * @pathtok: an array of strings containing the PATH env variable
 * @tokens: array of strings containing the tokenized command input
 */
void forkandexec(char **pathtok, char **tokens)
{
	pid_t cpid;
	int status;
	int i = 0;
	char temp_path[256];
	size_t len;

	cpid = fork();
	if (cpid == -1)
	{
		perror("Forking Error");
		exit(1);
	}
	else if (cpid == 0)
	{
		while (pathtok[i] != NULL)
		{
			len = strlen(pathtok[i]);
			if (tokens[0][0] == '/' && access(tokens[0], X_OK) == 0)
				/* if input starts with /, execute with absolute path */
			{
				execve(tokens[0], tokens, environ);
				perror("Execution error");
				exit(1);
			}
			if (len > 0 && pathtok[i][len - 1] != '/')
			{
				strncpy(temp_path, pathtok[i], sizeof(temp_path) - 1); /* copies path */
				strncat(temp_path, "/", sizeof(temp_path) - len - 1);
				/* only adds / if not there already */
			}
			else
			{
				strncpy(temp_path, pathtok[i], sizeof(temp_path) - 1); /* copies path */
			}
			temp_path[sizeof(temp_path) - 1] = '\0'; /* null terminates */
			strncat(temp_path, tokens[0], sizeof(temp_path) - strlen(temp_path) - 1); 
			/* command added to end of path */
			if (access(temp_path, X_OK) == 0) /* checks for executable permission */
			{
				execve(temp_path, tokens, environ);
				perror("Execution error");
				exit(1); /*in case of execve failure */
			}
			i++; /* increments to next element in path array */
		}
		fprintf(stderr, "Command not found: %s\n", tokens[0]);
		exit(1);
	}
	else
	{
		waitpid(cpid, &status, 0);
		printf("\n"); /* next shell prompt printed on a new line */
	}
}
