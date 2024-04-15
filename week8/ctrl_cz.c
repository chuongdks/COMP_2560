#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){  
	int i;
	void (*oldHandler1)(); //to save default handlers  
	void (*oldHandler2)(); //for CTRL-C and CTRL-Z

	/*
	Explanation:
	_ signal() change how a signal is handle (hence the name signal handler), 
	_ By default, when u press Ctrl + C, it will terminate a process or Ctrl + Z, it will put the process in a background
	_ Using signal() like below, the signal will be ignored instead, using the parameter SIGN_IGN
	_ The signal() return value is the previous value of the signal handler. It will store the default/original action when u trigger the signal
	_ signal() return value need to be store in a function pointer
	_ Ex: It will remember the terminate process of the Ctrl + C signal and return it if u want to keep that
	*/

	oldHandler1 = signal(2, SIG_IGN);	//ignore CTRL-C (SIGINT) and store the old signal handler of that specific signal
	oldHandler2 = signal(20, SIG_IGN); // ignore CTRL-Z (SIGTSTP)   ; kill -l   24-->20

	for(i=1; i<=10; i++)
	{
		printf("I am not sensitive to CTRL-C/CTRL-Z\n");  
		sleep(1);
	}

	signal(2, oldHandler1); // call signal to use the default action of CTRL + C
	signal(20, oldHandler2); // call signal to use the default action of CTRL + Z 

	for(i=1; i<=10; i++)
	{
		printf("I am sensitive to CTRL-C/CTRL-Z\n");  
		sleep(1);
	}
}

