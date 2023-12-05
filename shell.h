#ifndef SHELL_H
#define SHELL_H

extern char **environ;

#define MAX_PATH_LEN 256

char* find_executable(const char *command, char *env[]);
int main(void);

#endif
