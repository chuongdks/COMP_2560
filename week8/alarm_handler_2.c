#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int);

void alarm_handler(int dummy)
{
	printf("I got an alarm, I took care of signal %d\n", dummy);  
	signal(14, alarm_handler); //install handler
	alarm(3);
}

int main(int argc, char *argv[]){

	signal(14, alarm_handler);//install handler  alarm(3);	// for first time

	while(1)
	{
		printf("I am working\n");  sleep(1);
	}
}
