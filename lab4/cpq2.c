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
	signal(20, SIG_IGN); // ignore CTRL-Z (SIGTSTP) 

	pid=fork();
    if (pid == 0) // Child
    {
        // Pause the child until kill signal received
        pause();
        
        // During this time, the child have a handler for Ctrl + C and Ignore Ctrl + Z
        int inf = 8;
        while (inf > 0)
        {
            printf("I am not vulnerable to Ctrl + C\n");
            sleep(1);
            inf--;
        }
        
        // After this line, the child return to default handler for Ctrl + C and still Ignore Ctrl + Z
        printf("I am the child. Vulnerable to Ctrl + C\n");  
        execlp("./donothing","donothing",NULL);
    }
    else // Parent
    {
        printf("I am in parent process. Letting my child execute the infinite donothing program\n");
        // send a signal to child
        kill(pid, SIGINT);  
        kill(pid, SIGTSTP); 
        wait(NULL); // Stopped the parent procecss from exiting so that child process doesnt become orphan
    }
}

