#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MSGSIZE 16

char *msg1 = "hello, world #1";


int main() {
        char inbuf[MSGSIZE];
        int p[2], j;

        if (pipe(p) == -1) {  //create a pipe
                perror("pipe call");
                exit(1);
        }

	write(p[1], msg1, MSGSIZE);
        
	int rt= read(p[0], inbuf, MSGSIZE);

	printf(" I have read %d  bytes. \n", rt);
        printf(" This is what I read: %s \n", inbuf);
	
	close(p[1]);  //close the write end of the pipe
	printf(" I just closed the write end of the pipe and I will attempt to read again...\n");

	rt=read(p[0], inbuf, MSGSIZE); 
	
	printf(" I have read %d  bytes. \n", rt);
        printf(" This is what I read: %s \n", inbuf);
	printf(" Please read the \" read \" function manual page to see how it works with a pipe. \n");
}
