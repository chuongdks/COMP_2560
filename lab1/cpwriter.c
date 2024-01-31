#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    int fd1;
    char *filename = "list1.txt";

    // Open fd1 in write-only mode, create if not exists, truncate if exists
    if ((fd1 = open (filename, O_WRONLY | O_CREAT | O_TRUNC, 0700)) == -1)
    {
        perror("file open/create problem ");  
        exit(1);
    }

    // Write content to the file, 3 spaces are just 3 spaces, and a tab is \t
    write (fd1, "1011   GM\tBuick\t2014\n1024   Ford\tLincoln\t2025", 45);

    close(fd1);  

    return 0;
}
