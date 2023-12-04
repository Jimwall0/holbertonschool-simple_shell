#include <stdio.h>
#include <unistd.h>
/**
 * sh - basic shell
 * @string: commands
 * Return: 0
 */
int sh(void)
{
  /*sets a buffer and buffer size*/
  size_t buffsize = 32;
  char *buffer;
  char *argv[] = {"/bin/ls", "PATH", NULL}
  printf("Insert Command\n");
  getline(&buffer, &buffsize, stdin);
  
