#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){  
    void (*oldHandler1)(); //to save default handlers  
    void (*oldHandler2)(); //for CTRL-C and CTRL-Z

    oldHandler1 = signal(2, SIG_IGN); //ignore CTRL-C  
    oldHandler2 = signal(20, SIG_IGN); // ignore CTRL-Z

    if(fork()!=0) // During the first 10 seconds, Parent and Child both ignore Ctrl + C/Z. After that, only parent restore to Default Action and child keep ignoring
    {
        for(int i = 1; i <= 10; i++)
        {
            printf("Parent: I am not sensitive to CTRL-C/CTRL-Z\n");  
            sleep(1);
        }
    }
    else 
    {
        while(1)
        {
            printf("Child: I am not sensitive to CTRL-C/CTRL-Z?\n");  // Use Ctrl + D (EOF) or kill to terminate
            sleep(1);
        }
    }
}