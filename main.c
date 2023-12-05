#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc __attribute__((unused)), char **argv, char **env)
{
  char *line = NULL;
  char *command;
  pid_t pid;
  char *full_path;
  size_t len = 0;
  ssize_t read;
  /*keep running the program*/
  while (1)
    {
      /*prompt user*/
      printf("$ ");
      read = getline(&line, &len, stdin);
      
      if (read == -1)
        {
	  printf("\n");
	  break;
        }
      /*splits the the users input*/
      command = strtok(line, " ");
      if (command != NULL)
        {
	  /*look through the pathway to find the right command*/
	  full_path = find_executable(command, env);
	  if (full_path != NULL)
            {
	      /*sets the command*/
	      argv[0] = full_path;
	      argv[1] = NULL;
	      /*starts the child proccess*/
	      pid = fork();
	      
	      if (pid == -1)
                {
		  perror("Error forking");
		  exit(EXIT_FAILURE);
                }
	      
	      if (pid == 0)
                {
		  printf("Command: %s \n", command);
		  
		  if (execve(full_path, argv, env) == -1)
                    {
		      perror("Error executing command");
		      exit(EXIT_FAILURE);
                    }
		  free(full_path);
		  return (0);
                }
	      else
                {
		  wait(NULL);
                }
	      free(full_path);
            }
	  else
            {
	      fprintf(stderr, "Error: Command not found in PATH.\n");
            }
        }
    }
  
  free(line);
  
  return 0;
}
