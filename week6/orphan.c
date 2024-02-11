#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){  
	printf("Before fork\n");

	if ( fork() == 0 ){ // child
		printf("My parent is %d\n", getppid());  
		sleep(6);
	
		printf("My parent is %d\n", getppid());  
		exit(2);
	}
	// parent
	printf("had a child...\n");

	sleep(3);

	exit(1);
}

