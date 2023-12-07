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

char* find_executable(const char *command, char *env[]);
int main(int argc, char **argv);

#endif
