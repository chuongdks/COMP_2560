#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[]){  
	int pid, increase = 1;

	if((pid=fork()) != 0) //parent  
	{
		sleep(5);
		kill(pid, SIGSTOP);  // send the child SIGSTOP to stop the child process
		sleep(5);
		kill(pid, SIGCONT);  // send the child SIGCONT to continue the child process
		sleep(5);
		kill(pid, SIGINT);  // send the child SIGINT to terminate the child process
	}
	else //child code
	{
		while(1)
		{
			printf("Counter: %d\n", increase++);
			sleep(1);
		}
	}
}



