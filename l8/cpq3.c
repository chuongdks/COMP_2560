#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MSGSIZE 16

char *msg1 = "hello, world #1";
char *msg2 = "hello, world #2";

int main() {
        char inbuf[MSGSIZE];
        int p[2], j;

        if (pipe(p) == -1) //create a pipe
        {  
                perror("pipe call");
                exit(1);
        }

	write(p[1], msg1, MSGSIZE);
        // write(p[1], msg2, MSGSIZE);

        int rt = read(p[0], inbuf, 32);
        printf("I have requested to read 32 bytes, but only  %d  bytes in the pipe so far.\n", rt);
        printf("This is the  %d  bytes I read: %s\n", rt, inbuf);

	// rt = read(p[0], inbuf,  32);
        // printf("I have requested to read 32 bytes, but only  %d  bytes in the pipe so far.\n", rt);
        // printf("This is the  %d  bytes I read: %s\n", rt, inbuf);
}
