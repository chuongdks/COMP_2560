#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int dummy)
{
	printf("DING!!!\n");
	printf("Done\n");
}

int main(int argc, char *argv[]){
    if (argc != 2) {
        printf("Please enter the sleep duration as a CMD Line Argument\n");
        return 1;
    }

	int sleepTime = atoi(argv[1]);
	if (sleepTime <= 0) 
	{
		printf("Sleep time must be greater than 0!\n");
		return 1;
	}

	int pid;
	
	pid=fork();
    if (pid == 0) // CHild
    {
		printf("Alarm application running\n");  
		printf("Watiing for alarm to go off\n");  
		sleep(sleepTime);
        kill(getppid(), SIGALRM);
    }
    else // Parent
    {
		signal(14, alarm_handler);
		pause();
    }	
}
