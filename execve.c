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
	char temp_path[128];
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
			strncpy(temp_path, pathtok[i], sizeof(temp_path) - 1); /* copies path */
			temp_path[sizeof(temp_path) - 1] = '\0'; /* null terminates */
			len = strlen(temp_path);
			if (len > 0 && temp_path[len - 1] != '/')
			{
				strcat(temp_path, "/"); /* only adds / if not already there */
			}
			strcat(temp_path, tokens[0]); /* command added to end of path */

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
	}
}
