#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MSGSIZE 16

char *msg1 = "hello, world #1";

int main() {
        char inbuf[MSGSIZE];
        int p[2], j, pid;

        if (pipe(p) == -1) //create a pipe
        {  
                perror("pipe call");
                exit(1);
        }

        if ((pid = fork()) > 0) 
        {
                // Read msg1
                int rt = read(p[0], inbuf, MSGSIZE);
                printf(" I have read %d bytes. \n", rt);
                printf(" This is what I read: %s \n", inbuf);
                printf(" Sleeping until the write end has some inputs\n");

                // close the write end
                close(p[1]);  //close the write end of the pipe
                printf(" I just closed the write end of the pipe and I will attempt to read again...\n");

                
                // Try to read after all data has been read, read() will return 0
                rt = read(p[0], inbuf, MSGSIZE);                 
                printf(" I have read %d bytes. \n", rt);
                printf(" This is what I read: %s \n", inbuf);
                printf(" Please read the \" read \" function manual page to see how it works with a pipe. \n");        
        } 

        else 
        { 
                write(p[1], msg1, MSGSIZE);
                close(p[0]);  //close the read end of the pipe
        } 


}
