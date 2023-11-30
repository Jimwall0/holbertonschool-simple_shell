#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *argv[] = {"/bin/ls", "-l", NULL};
	/* path to file is first argument */
	/* must be terminated by NULL pointer */

	int val = execve(argv[0], argv, NULL);
	/* argv[0] refers to first element of argv array */
	/* defined above, this is the filename */

	if (val == -1) /* execve returns -1 on error */
		perror("Error");

	printf("Done with execution");
	/* This WON'T print on success because execve */
	/* overrides any text/data with loaded program */

	return (0);
}
