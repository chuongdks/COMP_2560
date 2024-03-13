#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int);

void alarm_handler(int dummy){
	printf("I got an alarm, I took care of signal %d\n", dummy);  // not recommended to printf a signal handling function
	alarm(3);  // The alarm signal handling will be trigger again!
}

int main(int argc, char *argv[]){
	// install handler, no function ptr to handle return signal like in ctrl_cz.c
	signal(14, alarm_handler); // The signal() function will call the alarm_handler() function when an alarm called SIGALRM (14), is activated after 3s
	alarm(3);

	while(1)
	{
		int counter;
		printf("Signal handler function will activate the alarm_handler function in %d\n", counter++);  
		sleep(1);
	}
}
