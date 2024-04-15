#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){  
	alarm(4);

	int pid=fork();  
	
	// The Parent process will trigger the alarm and got terminated, and the Child process will continue
	while(1){
		if(pid==0)
			printf("I am the child \n");  
		else 
			printf("I am the parent, child pid=%d\n", pid);  

		sleep(1);
	}
}
