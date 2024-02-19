#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){  
	int pid;

	pid = fork();
	
	if (pid) // means pid !=0
	{  
		printf("I am the parent process, pid=%d\n", getpid());  
		while(1)
		{
			sleep(20); // type ps -u pham75 during parent sleeping time to see the defunct, and after that it is normal again
			exit(0); 
		}
	}
	
	printf("I am the child process, pid=%d\n", getpid()); // type ps -u pham75 and find the parents and child pid to see the <defunct> state
    exit(0);
}

