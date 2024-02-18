#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char* argv[]) { 

        int pid;
	printf("Before: process id %d\n",getpid());

	if ((pid = fork())==0)
	{
		printf("I am the child %d\n",getpid());  
		sleep(5);
		printf("Listing content of current directory...\n");  
		execl("/bin/ls","ls","-l", "-t", (char *)0);
	    perror("sth is wrong.");
		
	}
	else{
		printf("I am the parent %d\n", getpid());  

		int status;
		int term_pid = wait(&status);
		printf("Child %d has listed the content of current directory\n",
			 term_pid);  
		exit(1);
	}
}

