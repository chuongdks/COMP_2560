#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){  
	int i;
	void (*oldHandler1)(); //to save default handlers  
	void (*oldHandler2)(); //for CTRL-C and CTRL-Z

	oldHandler1=signal(2, SIG_IGN);	//ignore CTRL-C  
	oldHandler2=signal(20, SIG_IGN); // ignore CTRL-Z  kill -l   24-->20

	for(i=1; i<=10; i++){
		printf("I am not sensitive to CTRL-C/CTRL-Z\n");  
		sleep(1);
	}
	signal(2, oldHandler1); // restore default  
	signal(20, oldHandler2); // restore default  

	for(i=1; i<=10; i++){
		printf("I am sensitive to CTRL-C/CTRL-Z\n");  
		sleep(1);
	}
}

