#ifndef SHELL_H
#define SHELL_H

#define MAX_PATH_LEN 256
#define MAX_NUM_ARGS 16
#define MAX_ARG_SIZE 64

extern char **environ;

int main(void);
char *findpath(char **env);
char **maketoken(char *str, char *delim);
void forkandexec(char **pathtok, char **tokens);
void free_array(char **array);

#endif
