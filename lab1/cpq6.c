#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp = NULL;
    char ch, string[100];
    int counter = 0;

    //1. Open the file
    if ((fp = fopen (argv[1], "r")) == NULL) 
    {
        printf("Error opening file. Make sure the file exists and is readable.\n");
        exit(1);
    }

    //2. While not at the EOF, display each character if the file
    while((ch = getc(fp)) != EOF)
	{
        fputc(ch, stdout);
	}

    //3. User enter information
    printf("\nPlease enter the information to be appended to the file: ");
    scanf("%s", string);

    //4. Append the info received to the end of the file
    fclose (fp); //Close the file
    fp = fopen (argv[1], "a");
    fprintf(fp, "%s", string);
     
    //5. Display again
    fclose (fp); //Close the file
    fp = fopen (argv[1], "r");

    while((ch = getc(fp)) != EOF)
	{
        fputc(ch, stdout);
	}

    printf("\n");
    fclose (fp); //Close the file
    exit(0);
}