//ex5.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *f;
	int c;

	f=fopen(argv[1], "w");  

	//
	setvbuf (f, NULL, _IOLBF, 512);

	while((c=getchar()) != EOF)
	{
		fputc(c, f);
	}
		
	//fclose (f); //Question: what happens if we exit with a CTRL-C? File will not be save, press Ctrl + D instead
}
