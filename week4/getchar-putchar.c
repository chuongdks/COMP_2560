#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int c; //change to char c or unsgined char c   ?

	while ((c = getchar()) != EOF)
	{
		fflush(stdin);
		putchar(c); fflush(stdout);

		
	}
	
	
}
