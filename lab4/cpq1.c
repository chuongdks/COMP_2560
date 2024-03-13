#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>  
#include <sys/wait.h>

int main(){  
	for (int i=0; i < 2; i++)
 	{
		// Orphan child 
		if (i == 0)
		{
			if ( fork() == 0 ) // If this is a child
			{
				printf("1st child created. PID = %d\n", getpid());
				printf("Becoming Orphan\n");
				sleep(3); // First Child got orphaned cuz sleeping while parent has already exited with the second child
				printf("1st child PID = %d, the parent is: %d\n", getpid(), getppid());
				exit(0);
			}			
		}

		// Nornal child that parent waited for
		if (i == 1)
		{
			if ( fork() == 0 ) // If this is a child
			{
				printf("2nd child created. PID = %d\n", getpid());
				printf("I will be waited by my parent...\n");
				exit(47);
			}			
		}
	}
	printf("Parent waited for pid = %d successfully", wait(NULL));
	exit(1);
}

