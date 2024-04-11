#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//void myAlarmHandler(int);
// to avoid program being terminated when signal alarmed happened (default action is terminated the signal)
void myAlarmHandler(int dummy)
{
	printf("to avoide to be terminted.\n");
} 

int main(int argc, char *argv[]){
	int pid;

	if((pid=fork()) > 0) //parent process code
	{ 
		printf("My child should wait until I am done\n"); 
		printf("Child, now you can do your job\n"); 
		sleep(4);
		kill(pid, SIGALRM); // let the child wake up, send ALARM to the child
		printf("Parent Exiting\n");
	}
	else //child process code
	{ 
		printf("I have to wait for my parent\n");  
		signal(SIGALRM, myAlarmHandler); // instruction on how to handle SIGALARM
		pause(); // Child PAUSE will be wake up by the kill() function
		printf("OK, now I can do my job\n");  
		sleep(2);
		printf("Child Exiting\n");
	}
	exit(0);
}

//parent    child
//kill      pause

