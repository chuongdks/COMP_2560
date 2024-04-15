#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<sys/wait.h>
/*
	Same program as pipe2.c and pipe1.c but has fork() and proper closing of Read-end and Write-end
*/
#define MSGSIZE 16

char *msg1 = "hello, world #1";
char *msg2 = "hello, world #2";
char *msg3 = "hello, world #3";

int main() {
	char inbuf[MSGSIZE];
	int p[2], j; // p[0] is the Pipe Read-end, p[1] is the Pipe Write-End
	pid_t pid;

	if (pipe(p) == -1){
		perror("pipe call error!");
		exit(1);
	}

	switch (pid = fork()) 
	{
		case -1:
			perror("fork call");
			exit(2);
		case 0:	//child process	
			close(p[0]); // Close the Read-End since Child is the Writer
			write(p[1], msg1, MSGSIZE);
			write(p[1], msg2, MSGSIZE);
			write(p[1], msg3, MSGSIZE);
			break;

		default: // parent process
			close(p[1]); // Close the Write-End since Parent is the Reader
			for (j = 0; j < 3; j++)
			{
				read(p[0], inbuf, MSGSIZE);
				printf("%s\n", inbuf);
			}
			wait(NULL); // Wait for the child to finished writing
	}
	exit(0);
}

