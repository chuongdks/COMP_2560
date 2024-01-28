#include <stdio.h>  
#include <stdlib.h>
#include <unistd.h>

int main(void){

	printf("Hello, my PID is %d\n", getpid());  
	printf("Hello, my PPID is %d\n", getppid());  
	exit(0);
}

