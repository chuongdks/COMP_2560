#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(){  
	int pid;
	alarm(4);  
	
	pid=fork();
	
	if(pid==0) // When the alarm is triggered, since Child process has the exec() cmd, the Child is a new process so it does not block the alarm, gets terminated
	{
		alarm(5);
		printf("I am the child\n");  
		sleep(2);
		execlp("./donothing","donothing",NULL);
	}
	else while(1)
	{
		printf("I am the parent, child pid=%d\n", pid);  
		sleep(1);
	}
}

