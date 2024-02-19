#include <stdio.h>

//how to demo this prog?
int main (int argc, char *argv[]) {

	while(--argc>0)
	    printf("%s ", *++argv);
	    // printf("%s ", argv[argc]); print in reverse order

	printf("\n");

}
