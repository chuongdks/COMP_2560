//ex5.c, run it as ./a.out ex5.txt
#include <stdio.h>

int main(int argc, char *argv[]){ 
	FILE *f = NULL;
	char c;

	f=fopen(argv[1], "w");  

	while((c=getchar()) != EOF)
	{
		fputc(c, f);
		//	fputc('h', f); // cast 'h' to 0x 00 23 (int)
	}
	
	// fclose (f); //Do we need this?
}


//Question: what happens if we exit with a CTRL-C? File will not be save, press Ctrl + D instead
