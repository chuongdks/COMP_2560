#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void action(int dummy)
{  
	sleep(1); 
	printf("Switching\n");
}

int main(int argc, char *argv[]){  
	int pid;

	if((pid=fork())>0) //parent  
	{
		sleep(1);
		while(1)
		{
			printf("Parent is running\n");  
			signal(SIGUSR1, action);  // when the SIGNAL happened to the parent (sent by Child using kill()), do action()
			kill(pid, SIGUSR1);  // send the child user-defined signal 1
			pause(); // pause until received signal 
		}
	}
	else //child code
	{
		while(1)
		{
			signal(SIGUSR1, action);  // when the SIGNAL happened to the child (sent by Parent using kill()), do action()
			pause(); // pause until received signal 
			printf("Child is running\n");  
			kill(getppid(), SIGUSR1); // send the parent user-defined signal 1
		}
	}
}

//parent    child
//kill      pause
//pause     kill


