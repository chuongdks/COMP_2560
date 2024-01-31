#include <stdio.h>
#include <stdlib.h>

// Buffer to hold the string
char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(int argc, char *argv[]) {
    FILE *fp = NULL;

    // Open file for writing (create if not exists, truncate if exists)
    if ((fp = fopen ("file.hole", "w")) == NULL) 
    {
        perror("fopen error");
        return 1;
    }

    // Write to file fp using the string buf1
    fprintf (fp, "%s", buf1);

    // Move file pointer to create a hole using fseek() function
    if (fseek (fp, 15, SEEK_SET) == -1) //fseek() and seek() are mostly the same
    {
        perror("fseek error");
        return 1;
    }

    // Write to file again
    fprintf (fp, "%s", buf2);

    // Close file
    fclose(fp);

    return 0;
}
