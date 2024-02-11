#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>

int main() {  
	int newpid;
	
	printf("before: mypid is %d\n", getpid());  

	if ((newpid = fork()) == -1 )
		perror("fork");  
	else if (newpid == 0){
		printf("I am the child %d now sleeping...\n",getpid());  
		sleep(5);
		abort();  //terminate abnormally
	}
	else{
		printf("I am the parent %d\n",getpid());  

		int status;
		int child_pid  = wait(&status);

		printf("My child %d has terminated\n",child_pid);
		printf("I have received the status = %\n",status);  

		//could you change the following using macros.
		int child_status = status >> 8;
		
		int signal = status & 0x7F;  
		int core = status & 0x80;

		printf("Child status = %d Signal = %d Core = %d\n",
				child_status, signal, core);
	}
}



