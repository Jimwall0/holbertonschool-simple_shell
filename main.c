#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
