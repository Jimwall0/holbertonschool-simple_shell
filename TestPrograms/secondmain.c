#include "shell.h"
int main(int argc __attribute__((unused)), char **argv)
{
  char *line = NULL;
  pid_t pid;
  size_t len = 32;
  while (1)
    {
      printf("$ ");
      getline(&line, &len, stdin);
      argv[0] = strtok(line, "\n");
      pid = fork();
      if (pid == 0)
	{
	  execve(argv[0], argv, environ);
	}
      wait(NULL);
    }
  return (0);
}
