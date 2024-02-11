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
	else if (newpid == 0){  //child process
		printf("I am the child %d now sleeping...\n",getpid()); 
		sleep(2);
		exit(47);
		printf("I am gone");
	     }
	else{  //parent process
		printf("I am the parent %d\n",getpid());  

		sleep(10);
		printf("My child %d must be gone by now. I am leaving...\n",newpid);
                exit(1);
		printf("I am gone too\n");
		
	}
}



