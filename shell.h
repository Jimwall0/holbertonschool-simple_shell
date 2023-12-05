#ifndef SHELL_H
#define SHELL_H

#define MAX_PATH_LEN 256

char* find_executable(const char *command, char *env[]);
int main(int argc, char **argv, char **env);


#endif
