//**************************************************************************************************************************************************
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include<stdlib.h>

//interesting progam to figure out what's going on.
//and see how coordination is achieved

int ntimes = 0;

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
		case 0:  //child n
			signal(SIGUSR1, c_action);
			
			ppid = getppid();
			
			for (;;)
			{
				sleep(1);
				kill(ppid, SIGUSR1);
				pause();
				//pause(); 
				//sleep(1);
				//kill(ppid, SIGUSR1); 
			}
		default: 
		
			for (;;)
			{
				pause();
				sleep(1);
				kill(pid, SIGUSR1);
			}
	}
}


