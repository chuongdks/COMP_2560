#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){  
	printf("Before fork\n");

	if (fork() == 0) // child
	{ 
		printf("My parent is %d\n", getppid());  

		sleep(6);
	
		printf("My parent is %d\n", getppid()); // Kernal/Init will change the PPID of child process to 1 --> Orphan processes are adopted by proces init (whose PID = 1)
												// Init accpet all its children returns
		exit(2);
	}
	// parent
	printf("had a child...\n");
	// sleep(6);
	exit(1);
}

