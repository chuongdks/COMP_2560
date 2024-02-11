#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *combinedFile;
    FILE *ifp;
    int c;
    int i;

    // Open the combined file for writing
    if ((combinedFile = fopen (argv[argc - 1], "w")) == NULL) 
    {
        perror("Error opening combined file. Make sure the file exists and is readable.\n");
        return 1;
    }

    // Loop through each input file and append its content to the combined file
    while(--argc > 0) // Minus argc at the beginning cuz argv start at index 0
    {
        if ((ifp = fopen(*++argv, "r")) == NULL) // argv[1] == *(argv+1), plus one at the beginning to exclude the program name argument
        {
            perror("Error opening input file");
            return 1;
        }

        // Read and write each character from the input file to the combined file
        while ((c = getc(ifp)) != EOF) 
        {
            fputc (c, combinedFile);
        }

        // Close the input file
        fclose(ifp);
    }

    // Close the combined file
    fclose(combinedFile);
    return 0;
}
