#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){  
	alarm(4);
	while(1){
		printf("Going to sleep\n");  
		sleep(1);
	}
	
	printf("Exiting\n");//will not be executed 

	exit(0);
}
  
