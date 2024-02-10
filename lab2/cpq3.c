#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

void filecopy(int ifd, int ofd);

int main(int argc, char* argv[]) {
    int ifd;

    if (argc == 1) 
    {
        filecopy (0, 1); // stdin = 0, stdout = 1, stderr = 2
    } 
    else 
    {
        while(--argc >0) // Minus argc at the beginning cuz argv start at index 0
        {
            if ((ifd = open(*++argv, O_RDONLY)) == -1) // argv[1] == *(argv+1), plus one at the beginning to exclude the program name argument
            {
                printf ("cat: can not open %s\n", *argv);
                exit(1);
            }
            else
            {
                filecopy (ifd, 1);
                close(ifd);
            }
        }
    }
    exit(0);
}

// Use read() and write() to get buffer from *ifp to *ofp
void filecopy (int ifd, int ofd) 
{
    char buffer[512];
    int readSize;
    
    while ((readSize = read (ifd, buffer, 512)) > 0) 
    {
        if (write (ofd, buffer, readSize) != readSize) 
        {
            perror ("writing problem "); 
            exit(3);
        }
    }
}
