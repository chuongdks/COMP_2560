#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Code to Demonstrate an Orphan process
// a parent exits (for example, the parent has been killed prematurely) while its children are still alive. The children become orphans.
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

// Code to Demonstrate a Zombie process
// The parent is alive but never makes the call to wait().  The children become zombies.
int main(int argc, char *argv[]){  
	int pid, status;

	pid = fork();
	
	if (pid) // means pid !=0
	{  
		printf("I am the parent process, pid=%d\n", getpid());  
		while(1)
		{
			sleep(20); // type ps -u pham75 during parent sleeping time to see the defunct, and after that it is normal again if u uncomment the line below
			// exit(0); 
		}
	}
	
	printf("I am the child process, pid=%d\n", getpid()); // type ps -u pham75 and find the parents and child pid to see the <defunct> state
    exit(0);
}
