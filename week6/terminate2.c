#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>

int main() {  
	int newpid;

	printf("before: mypid is %d\n", getpid());  

	if ((newpid = fork()) == -1 )
	{
		perror("fork");  
	}
	else if (newpid == 0)
	{
		printf("I am the child %d now sleeping...\n", getpid());  
        sleep(20); 
		exit(47);  //47 == 0x2F
	}
	else
	{
		printf("I am the parent %d\n",getpid()); 
		
		int status; 
		
		int child_pid = wait(&status);  // If the child is terminated normally. It will exit with number 47 (0x2F) put in the leftmost byte. 
		// Gonna shift it ourself to show the child status. 0x2F00 >> 8 = 0x002F, it shift 8 bits to the right 0010 1111 0000 0000 >> 8 = 0010 1111
		// Also wait() and waitpid() function return the child's pid, will use this fact for status2.c

		/* 
		If the rightmost byte of status is zero, then the left most byte contains the status returned by the child: 
		a value between 0 and 255 (passed as an argument to exit).
		This represents a normal termination of the child process. 

		If the rightmost byte of status is nonzero, then the rightmost 7 bits are equal to the signal number that caused the process to terminate. 
		The remaining bit of the rightmost byte is set to 1 if a core dump was produced by the child process.
		*/

		/*
		How to kill a child process while it is sleeping: open another cmd terminal and type "kill *child_pid*"
		ex: kill 1234
		*/

		printf("My child %d has terminated\n", child_pid);
		printf("I have received the status = %x\n",status); 

		int child_status = status >> 8; // Shift the status by 8 bit, 0x2F00 >> 8 = 0x002F
	
		int signal = status & 0x7F;  // Do it for the signal on the right most
		
		int core = status & 0x80; // Do it for the core on the right most (MSB)

		printf("Child status = %d\tSignal = %d\tCore = %d\n",child_status, signal, core);
	}
}

