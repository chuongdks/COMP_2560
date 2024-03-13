#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void signal_handler(int signum)
{
	printf("Signal %d: %s\n", signum, strsignal(signum));
	printf("Test\n");
}

int main(int argc, char *argv[]){  
	int pid;

	if((pid=fork()) > 0) //parent process code
	{ 
		sleep(1);
		kill(pid, SIGINT);  // send the child SIGINT to terminate the child process
		kill(pid, SIGQUIT);  // send the child SIGINT to terminate the child process
	}
	else //child process code
	{ 
		signal(SIGINT, signal_handler);   
		signal(SIGQUIT, signal_handler);  
		pause(); // Child PAUSE will be wake up by the kill()
	}
	return 0;
}



