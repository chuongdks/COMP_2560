//copy file f1 to f2 using standard I/O
//we did something similar using system I/O

#include<stdio.h>

int copyfile(const char *f1, const char *f2)
{
	FILE *inf, *outf;
	int c;

	if ((inf = fopen(f1,"r")) == NULL)
	{
		return (-1);
	}

	if ((outf = fopen(f2, "w")) == NULL)
	{
//		fclose(inf);
		return (-2);
	}


	// while ((c=getc(inf)) != EOF) 
	// {
	// 	putc(c, outf); 
	// }

	// These functions return the same value whether an error occurs or the end of file is reached. 
	// To distinguish between the two, we must call either ferror or feof
	while(1) 
	{
		c = getc(inf);
		if ( feof (inf) ) 
		{ 
			printf("End of file reached\n");
			break;
		}
		if( ferror(inf) ) 
		{
    		printf("Error in reading from file\n");
			break;
   		}
   		clearerr(inf);

		putc(c, outf);
	}


	fclose(inf);
	fclose(outf);

	return (0);
}

int main(int argc, char * argv[])
{
	copyfile(argv[1], argv[2]);
}
