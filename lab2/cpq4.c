#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *ifp, *ofp;
    char buffer[512];
    int read;

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

    // Find the size of the file
    fseek (ifp, 0, SEEK_END);
    long fileSize = ftell(ifp);
    fseek (ifp, 0, SEEK_SET); // Return the cursor to the original position

    // Count the number of lines in the input file
    long position = fileSize - 1;
    int lines_count = 0;
    while (position >= 0) 
    {
        fseek (ifp, position, SEEK_SET);
        if (getc (ifp) == '\n') 
        {
            lines_count++;
        }
        position--;
    }

    // Read lines in reverse order and write them to the output file
    for (int i = lines_count; i > 0; i--) 
    {
        fseek (ifp, 0, SEEK_SET);
        for (int j = 0; j < i; j++) 
        {
            fgets (buffer, 512, ifp);
        }
        fputs (buffer, ofp);
    }

    // Close files and free memory
    fclose(ifp);
    fclose(ofp);

    return 0;
}
