#include<stdio.h>

int main(int argc, char* argv[])
{
	FILE *fp;

	void filecopy(FILE *, FILE *);

	if (argc == 1) // Use Keyboard input if use 1 argument only
	{
		filecopy(stdin, stdout);
	}
	else
	{
		while(--argc > 0) // Minus argc at the beginning to exclude the program name. Loop through each cmd line arguments 
		{
			if ((fp = fopen(*++argv, "r")) == NULL) // argv[1] == *(argv+1)
			{
				printf("cat: can not open %s\n", *argv);
				return 1;
			}
			else
			{
				filecopy(fp, stdout);
				fclose(fp);
			}
		}
	}

	return 0;
}

// Use fgets() and fputs() to get buffer from *ifp to *ofp
void filecopy(FILE *ifp, FILE *ofp)
{
    char buffer[512]; 

    while (fgets (buffer, 512, ifp) != NULL)
    {
        fputs (buffer, ofp);
    }
}


