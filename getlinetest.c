#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	size_t n = 10; /* buffer size */
	char *buf = malloc(sizeof(char) * n); /*creates buffer */

	printf("Enter name ");
	getline(&buf, &n, stdin); /* ADDRESS of buffer and size */
	
	printf("Name is %sBuffer size is %ld\n", buf, n);

	free(buf); /* free memory */

	return (0);
}	
