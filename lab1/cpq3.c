#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){ 
    char buffer[512]; 
    int fd1, fd2;
    int counter = 0;
    
    if (((fd1 = open (argv[1], O_RDONLY)) == -1))
    {
        perror("file open/create problem ");  
        exit(1);
    }

    //read up to '1' bytes from 'fd1' and store the read data into 'buffer'
    while (read (fd1, buffer, 1) > 0)
    {
        if (*buffer == '\n')
        {
            counter++;
        }
    }

    printf("Number of newlines in %s: %d newlines\n", argv[1], counter);
    close(fd1); 

    exit(0);
}

