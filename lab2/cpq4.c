#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *ifp, *ofp;
    char buffer[512];

    // Open the input file using read and write
    if ((ifp = fopen (argv[1], "r+")) == NULL) 
    {
        printf("Error opening file. Make sure the file exists and is readable.\n");
        return 1;
    }

    // Open the output file using write only
    if ((ofp = fopen (argv[2], "w")) == NULL) 
    {
        printf("Error opening file. Make sure the file exists and is readable.\n");
        return 1;
    }

    // Check if the input file ends with a newline
    fseek(ifp, -1, SEEK_END);
    if (fgetc(ifp) != '\n') 
    {
        fprintf(ifp, "\n");
    }

    // Return the cursor to the original position
    rewind(ifp);

    // Read lines from input file and store them in a String array
    char bufferReverse[100][512];
    int newLineCounter = 0;
    while (fgets (buffer, 512, ifp) != NULL)
    {
        strcpy (bufferReverse[newLineCounter], buffer);
        newLineCounter++;
    }

    // Print lines in reverse order to output file
    for (int i = newLineCounter - 1; i >= 0; i--)
    {
        fputs (bufferReverse[i], ofp);
    }

    // Close files
    fclose(ifp);
    fclose(ofp);

    return 0;
}
