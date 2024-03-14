#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

void signal_handler(int signum)
{
	printf("Signal %d: %s\n", signum, strsignal(signum));
}

int main(int argc, char *argv[]){  
	int pid;

	pid=fork();

    if (pid == 0) // Child
    {
		signal(SIGINT, signal_handler);   
		signal(SIGQUIT, signal_handler);  
		pause(); // Child PAUSE will be wake up by the kill()
		exit(1);
    }
    else // Parent
    {
		sleep(1); // put sleep here so that the child could set up the signal handler before hand
		// send a signal to child
		kill(pid, SIGINT);  // send the child SIGINT 
		kill(pid, SIGQUIT);  // send the child SIGQUIT 
		wait(NULL); // Stopped the parent procecss from exiting so that child process doesnt become orphan
    }	
	return 0;
}



