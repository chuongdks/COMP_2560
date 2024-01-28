#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp = NULL;
    char checker;
    int counter = 0;

    if ((fp = fopen (argv[1], "r")) == NULL) 
    {
        printf("Error opening file. Make sure the file exists and is readable.\n");
        exit(1);
    }

    //Count the line
    while((checker = getc(fp)) != EOF)
	{
		if (checker == '\n')
        {
            counter++;
        }
	}
    printf("Number of newlines in %s: %d newlines\n", argv[1], counter);
    //Close the file
    fclose (fp);

    exit(0);
}