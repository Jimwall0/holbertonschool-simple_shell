#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[] = "This is a string";
	char *delim = " "; /* space is set as delimiter */
	char *token; /*returned by strtok */

	token = strtok(str, delim); /* set result of strtok to token */

	while(token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, delim);
		/**
		 * reassigning *str to NULL moves token to next part
		 */
	}

	return (0);
}
