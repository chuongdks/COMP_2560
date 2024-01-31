#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp = NULL;
    char checker;
    int counter = 0;

    //open the file using read only
    if ((fp = fopen (argv[1], "r")) == NULL) 
    {
        printf("Error opening file. Make sure the file exists and is readable.\n");
        exit(1);
    }

    //Count the line using getc and store it in the char variable checker
    while((checker = getc(fp)) != EOF)
	{
        //if checker is equal to the char newline '\n', increase the counter
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