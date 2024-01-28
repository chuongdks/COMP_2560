#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){ 
    char buffer[512], string[100]; //buffer[] store the content of the file, string[] store the info from the keyboard
    int fd1; //file descriptor
    int size = 0; //keep track of the file size
    
    //1. Open fd1 for reading and writing mode, and Append to the end of file on each write
    if (((fd1 = open (argv[1], O_RDWR|O_APPEND)) == -1))
    {
        perror ("file open/create problem ");  
        exit(1);
    }

    //2. Read up to '1' bytes from 'fd1' and store the read data into 'buffer', then display it to stdout
    while ((size = read (fd1, buffer, 512)) > 0)
    {
        //write to stdout, write 'size' bytes from 'buffer' which store the content to be written
        //return value of write() is the number of bytes actually written, return -1 if error occured
        if (write (1, buffer, size) != size) //fd 0 (stdin), 1 (stdout), 2 (stderr)
        {
            perror ("Writing problem"); 
            exit(3);
        }
    }

    //3. User enter information
    printf("\nPlease enter the information to be appended to the file: ");
    scanf("%s", string);

    //4. Append the info received to the end of the file
    if (lseek(fd1, 0, SEEK_END) < 0) // position to EOF by using lseek SEEK_END
    {
        perror ("Lseek problem"); 
        exit(3);
    } 
    if (write (fd1, string, strlen (string)) != strlen (string)) // and write the file at EOF
    {
        perror ("Writing problem"); 
        exit(3);
    } 
    
    //5. Display to the user again
    // Reposition the file pointer to the beginning of the file
    if (lseek (fd1, 0, SEEK_SET) < 0) 
    {
        perror ("Lseek problem"); 
        exit(3);
    }   
    while ((size = read (fd1, buffer, 512)) > 0) //read up to '1' bytes from 'fd1' and store the read data into 'buffer', then display it to stdout
    {
        if (write (1, buffer, size) != size) //fd 0 (stdin), 1 (stdout), 2 (stderr)
        {
            perror ("Writing problem"); 
            exit(3);
        }
    }
    printf("\n"); //new line
    //Close the file
    close(fd1); 

    exit(0);
}

