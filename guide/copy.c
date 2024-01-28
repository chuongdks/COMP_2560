#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

//This program copy content of file1 to file2 using argument ./a file1 file2
int main(int argc, char *argv[]){ 
    char buffer[512]; 
    int fd1, fd2;
    long int n1;
    
    //open the file via argument, ex: ./test file1 file2, open() return -1 if fail to open file
    //argv[0] is the file itself, argv[1] and so on are the arguments
    //The program attempts to open the source file (argv[1]) in read-only mode and the destination file (argv[2]) in create/write-only/truncate mode. 
    if ( ((fd1 = open (argv[1], O_RDONLY)) == -1) || ((fd2 = open (argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0700)) == -1) )
    {
        perror("file open/create problem ");  
        exit(1);
    }
    printf("File Descriptor 1: %d\n", fd1);
    printf("File Descriptor 2: %d\n", fd2);

    //read up to '512' bytes from 'fd1' and store the read data into 'buffer'
    //return value is the number of byte actually read, if return 0 means it has reach EOF
    //for this loop, if n1 exceed 512, it will keep writing and concatinating until n1 = 0 ie reached EOF
    while ((n1 = read (fd1, buffer, 512)) > 0)
    {
        //Basically count how many characters in fd1 since 1 byte = 8 bits = 1 char and write them to fd2
        printf("n1 value during the loop: %d bytes\n", n1);
        
        //write to 'fd2', write 'n1' bytes from 'buffer' which store the content to be written
        //return value of write() is the number of bytes actually written, return -1 if error occured
        if (write (fd2, buffer, n1) != n1)
        {
            perror("writing problem "); 
            exit(3);
        }
    }
    printf("Read return %d bytes\n", n1);

    // in Case of an error exit from the loop  
    if(n1 == -1)
    {
        perror("Reading problem ");  
        exit(2);
    }
    close(fd1);
    close(fd2);  
    exit(0);
}

