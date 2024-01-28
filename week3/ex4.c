#include <stdio.h>
#include <unistd.h>	// needed for sleep()

//note the difference b/w ex3.c and ex4.c
//could you explain it?

int main(int argc, char *argv[]){  
	while(1){
		printf("Hello, program is runing right now\n");  
		sleep(1);
	}
}
