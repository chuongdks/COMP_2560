// C program to illustrate 
// pipe system call in C 
// shared by Parent and Child 
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <sys/wait.h>
#define MSGSIZE 16 
char* msg1 = "hello, world #1"; 
char* msg2 = "hello, world #2"; 
char* msg3 = "hello, world #3"; 
/*
	Program is like pipe1.c but Parent process Write instead of Child
	_ After the parent process writes data to the pipe and the child process reads from it
	_ The child process wait for more data to arrive, 
	_ But Parent process has finished writing and closed the Write-end
	_ If the child process continues waiting the program will hang.
	_ Must close the Write-end in both the Parent and Child
*/
int main() 
{ 
	char inbuf[MSGSIZE]; 
	int p[2], pid, nbytes; 

	if (pipe(p) < 0) 
		exit(1); 

	if ((pid = fork()) > 0) // Parent Proces
	{ 
		write(p[1], msg1, MSGSIZE); 
		write(p[1], msg2, MSGSIZE); 
		write(p[1], msg3, MSGSIZE); 

		close(p[1]);  // Adding this line will not hang the program 

		wait(NULL); // wait for the Child to finished reading
	} 
	else // Child Process
	{
		close(p[1]);  // Adding this line will not hang the program 

		while ((nbytes = read(p[0], inbuf, MSGSIZE)) > 0) 
		{
			printf("% s\n", inbuf); 
		}

		printf("Finished reading\n"); 
	} 
	return 0; 
} 
