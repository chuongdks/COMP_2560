#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) { 
	int fd, size;
	char c, buffer[512]; 

	if(argc == 1) //If there are no argument 
    {
        fd = 0; //Use stdin instead of file (0 = stdin)
    }
	else
    {
		if ((fd = open (argv[1], O_RDONLY)) == -1)
        {
            perror("file open problem ");  
            exit(1);
		}
    }

    while ((size = read (fd, buffer, 512)) > 0)
    {
        //write to stdout, write 'size' bytes from 'buffer' which store the content to be written
        //return value of write() is the number of bytes actually written, return -1 if error occured
        if (write (1, buffer, size) != size) //fd 0 (stdin), 1 (stdout), 2 (stderr)
        {
            perror ("Writing problem"); 
            exit(3);
        }
    }
    printf("\n");
    // in Case of an error exit from the loop  
    if(size == -1)
    {
        perror("Reading problem ");  
        exit(2);
    }
	exit(0);
}
