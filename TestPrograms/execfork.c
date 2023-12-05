#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;

        char *argv[] = {"/bin/ls", "-l", NULL};

	pid = fork(); /* fork creates child process */

	if (pid == -1) /* checks for failure */
		return (-1);

	if (pid == 0) /* checks if current process is child */
	{
		int val = execve(argv[0], argv, NULL);
	
		if (val == -1)
                	perror("Error");
	}
	else /* implies current process is parent */
	{
		wait(NULL); /* parent waits for child to finish */
        	printf("Done with execution\n");
	}

        return (0);
}
