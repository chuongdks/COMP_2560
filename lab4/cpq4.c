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

	signal(SIGINT, signal_handler);	// Ctrl + C
	signal(SIGQUIT, signal_handler); // Ctrl + \ 

    while (1)
    {
        sleep(1);
    }

	return 0;
}



