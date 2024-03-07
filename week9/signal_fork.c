//A child process inherits the signal setting from its parent during  a fork().

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]){  
	int i;
	void (*oldHandler1)(); //to save default handlers  
	void (*oldHandler2)(); //for CTRL-C and CTRL-Z

	oldHandler1=signal(2, SIG_IGN); //ignore CTRL-C,use integer for sig. no is not good
	oldHandler2=signal(SIGTSTP, SIG_IGN); // ignore CTRL-Z

	if(fork()!=0)
		for(i=1; i<=10; i++){
			printf("Parent: I am not sensitive to CTRL-C/CTRL-Z\n");  
			sleep(1);
		}
	else while(1){
		printf("Child: I am not sensitive to CTRL-C/CTRL-Z?\n");  
		sleep(1);
	}
}

// coudl you add some code later to terminate both the parent and child process
