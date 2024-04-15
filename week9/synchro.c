#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include<stdlib.h>

//interesting progam to figure out what's going on. And see how coordination is achieved

int ntimes = 0; // Global Variable

void p_action(int sig){
	printf("Parent caught signal #%d\n", ++ntimes);
}
void c_action(int sig){
	printf("Child caught signal #%d\n", ++ntimes);
}

int main(){
	pid_t pid, ppid;
	
	signal(SIGUSR1, p_action);

	switch (pid = fork()) {
		case -1: 
			perror("synchro");
			exit(1);
		case 0:  //child 
			signal(SIGUSR1, c_action);
			
			ppid = getppid();
			
			for (;;)
			{
				sleep(1);
				kill(ppid, SIGUSR1); // Send signal to Parent
				pause(); // Wating for Parent
			}
		default: // Parent
			for (;;)
			{
				pause(); // Wating for Child
				sleep(1);
				kill(pid, SIGUSR1); // Send signal to Child
			}
	}
}


