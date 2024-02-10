#include <stdio.h>

int main() {
    FILE *fp;

    for (int i = 1; i <= 30; i++) 
    {
        char filename[20];
        sprintf(filename, "file%d", i); // Creating file names like file_1.txt, file_2.txt, ...

        fp = fopen(filename, "w"); // Opening file for writing purpose

        if (fp == NULL) 
        {
            printf("Unable to create fp %s\n", filename);
            return 1;
        }

        fprintf(fp, "This is file number: %d\n", i); // Writing number or something to the file

        printf("file%d ", i); // Print something after each file created, print the name to copy them easily
        fclose(fp); // Closing file
    }
    return 0;
}
