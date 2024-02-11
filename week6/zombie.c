#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){  
	int pid;

	pid = fork();
	
	if (pid){  // means pid !=0
		printf("I am the parent process, pid=%d\n", getpid());  
		while(1)
			sleep(5);
	}
	
	printf("I am the child process, pid=%d\n", getpid()); 
        exit(0);
}

