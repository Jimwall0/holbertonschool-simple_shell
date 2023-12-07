#ifndef SHELL_H
#define SHELL_H
extern char **environ;
#define MAX_PATH_LEN 256
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void);
char *findpath(char **env);
char **maketoken(char *str, char *delim);
void forkandexec(char **pathtok, char **tokens);
void free_array(char **array);

#endif
