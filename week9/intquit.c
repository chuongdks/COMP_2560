#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigHandler(int sig) { // return which signal is called using parameter int sig
	static int count = 0;

	if (sig == SIGINT) 
	{
		count++;
		printf("Caught SIGINT (%d)\n", count);
		return; /* Resume execution at point of interruption */
    }
	/* Must be SIGQUIT - print a message and terminate the process */
	printf("Caught SIGQUIT - that's all folks!\n");  //how to produce SIGQUIT from keyboard
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
	/* Establish same handler for SIGINT and SIGQUIT */
	if (signal(SIGINT, sigHandler) == SIG_ERR){
		perror("signal");
		exit(4);
	}
	
	if (signal(SIGQUIT, sigHandler) == SIG_ERR){ // Ctrl + '\' to quit
		perror("signal");
		exit(4);
	}

	for (;;) /* Loop forever, waiting for signals */
		pause(); /* Block until a signal is caught */
}
