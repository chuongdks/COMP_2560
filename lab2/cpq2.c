#include<stdio.h>


int main(int argc, char* argv[])
{
	FILE *fp;

	void filecopy(FILE *, FILE *);

	if (argc == 1) // Use Keyboard input if use 1 argument only
	{
		setvbuf(stdout, NULL, _IOLBF, BUFSIZ);
		filecopy(stdin, stdout);
	}
	else
	{
		while(--argc >0) // Minus argc at the beginning to exclude the program name. Loop through each cmd line arguments 
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

// Use fread() and fwrite() to get buffer from *ifp to *ofp
void filecopy(FILE *ifp, FILE *ofp)
{
    char buffer[1024];
    int readSize; // Size of the bytes read by function fread()
	
    readSize = fread (buffer, 1, sizeof(buffer), ifp); // 'fread()' return size_t so store it in a variable
    fwrite (buffer, 1, readSize, ofp); // 'sizeof(buffer)' is too large for 'fwrite()', initialized garbage data, has to use data return by 'fread()'

	// while ((readSize = fread(buffer, 1, sizeof(buffer), ifp)) > 0) 
	// {
    //     fwrite(buffer, 1, readSize, ofp);
    //     fflush(ofp); 
    // }
}


