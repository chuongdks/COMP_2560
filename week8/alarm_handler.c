#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int);

void alarm_handler(int dummy){
	printf("I got an alarm, I took care of signal %d\n", dummy);  // not recommended to printf a signal handling function
	alarm(3);  //try uncomment this line to see what happens: the alarm signal handling will be trigger again!
}

int main(int argc, char *argv[]){

	signal(14, alarm_handler);//install handler, no function ptr to handle return signal like in ctrl_cz.c
	alarm(3);

	while(1){
		printf("I am working\n");  
		sleep(1);
	}
}
