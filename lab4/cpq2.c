#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void SIGINT_Handler(int dummy)
{
	printf("Ctrl + C is Pressed!\n");  // not recommended to printf a signal handling function
}

int main(int argc, char *argv[]){  
	int pid,i;

	signal(2, SIGINT_Handler);	//ignore CTRL-C (SIGINT) and store the old signal handler of that specific signal
	signal(20, SIG_IGN); // ignore CTRL-Z (SIGTSTP)   ; kill -l   24-->20

	pid=fork();
    if (pid == 0) // CHild
    {
        printf("I am the child\n");  
        execlp("./donothing","donothing",NULL);
    }
    else // Parent
    {
        printf("I am in parent process. Letting my child execute the infinite donothing program\n");
        wait(NULL); // Stopped the parent procecss from exiting
        // send a signal to child
        kill(pid, SIGINT);  
        kill(pid, SIGTSTP); 
    }
}

