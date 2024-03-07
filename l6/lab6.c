#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int glb = 100; // global variable  

int main(){
	int pid;
	int var = 88;  
	
	printf("Before fork\n");  
	pid = fork();

	if( pid < 0 ){  
		perror("fork");  
		exit(1);
	}
	
	if(pid == 0){ //child  
		
		int num =10;         
    		while(num==10){ // Child stuck in infinite loop
		        sleep(10);
		}

		glb++; var++;
	//	sleep(10);
		sleep(15);
	}
	else{ // parent
		sleep(2);
	}
	
	printf("pid = %d, glob = %d, var = %d\n", getpid(), glb, var);
	return 0;
}



