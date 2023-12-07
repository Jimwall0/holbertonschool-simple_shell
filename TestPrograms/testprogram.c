#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

#define MAX_PATH_LEN 256
#define MAX_CMD_LEN 256

char* find_executable(const char *command, char *env[]) {
    char *path_var = NULL;
    char *path_copy;
    char *dir;
    char full_path[MAX_PATH_LEN];

    for (int i = 0; env[i] != NULL; i++) 
    {
        if (strncmp(env[i], "PATH=", 5) == 0) /* checks first 5 characters for match */
	{
            path_var = env[i] + 5; /* Skip "PATH=" */
            break;
        }
    }

    if (path_var == NULL) 
    {
        fprintf(stderr, "Error: PATH variable not set.\n");
        return NULL;
    }

    path_copy = strdup(path_var); /* creates copy of path var that can be manipulated */
    if (path_copy == NULL) 
    {
        perror("Error");
        return NULL;
    }

    dir = strtok(path_copy, ":"); /* splits path into individual directories */
    
    while (dir != NULL) 
    {
        strcpy(full_path, dir);
	strcat(full_path, "/");
	strcat(full_path, command);
	/* builds full path by combining directory and command */

        if (access(full_path, X_OK) == 0) /* checks if file is executable */
	{
            free(path_copy);
            return strdup(full_path);
        }

        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

int main(void) 
{
    char *line = NULL;
    char *command;
    char *argv[2];
    pid_t pid;
    char *full_path;
    size_t len = 0;
    ssize_t read;

    while (1) 
    {
        printf("$ ");
        read = getline(&line, &len, stdin);

        if (read == -1) 
	{
            printf("\n");
            break;
        }

        command = strtok(line, " \n");

        if (command != NULL) 
	{
            full_path = find_executable(command, environ);

            if (full_path != NULL) 
	    {
                argv[0] = full_path;
                argv[1] = NULL;

                pid = fork();

                if (pid == -1) 
		{
                    perror("Error forking");
                    exit(EXIT_FAILURE);
                }

                if (pid == 0) 
		{
                    printf("Command: %s \n", command);

                    if (execve(full_path, argv, environ) == -1) 
		    {
                        perror("Error executing command");
                        exit(EXIT_FAILURE);
                    }
                } else 
		{
                    wait(NULL);
                }

                free(full_path);
            } else 
	    {
                fprintf(stderr, "Error: Command not found in PATH.\n");
            }
        }
    }

    free(line);

    return 0;
}

