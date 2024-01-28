//ex5.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *fp;
	int c;

	if (argc == 1)
	{
		fp = stdin; //keyboard
	}
	else
	{
		if ((fp = fopen (argv[1], "r")) == NULL)
		{
			fprintf(stderr, "Error opening %s. No suck file exist\n", argv[1]);
			exit(1);
		}
	}

	while((c = getc(fp)) != EOF)
	{
		fputc(c, stdout); //Press Ctrl + D to return EOF if use 'stdin' for 'fp'
	}
	printf("\n");
	//	fputc('h', f); // cast 'h' to 0x 00 23 (int)
	//fclose(f);   //do I need this sentence or not? ctl+D   

	exit(0);
}
