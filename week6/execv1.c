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
		
		char* arg_list[4] = {"The Argv[0] is just a name", "-l", "-t", (char *)0};
		// OR
		// char* arg_list[3];
		// arg_list[0] = "ls";
		// arg_list[1] = "-l";
		// arg_list[2] = 0;
		
		// Do execv or execvp by comment these 2 line here or the 2 lines below 
		execv("/bin/ls",arg_list);
		perror("execv failed!");

		execvp("ls",arg_list); //execvp("/usr/bin/ls", arg_list);
		perror("execvp failed!");
	}
	else
	{
		printf("I am the parent %d\n", getpid());  

		int status;
		int term_pid = wait(&status);
		//extract exit status using macros?
		printf("Child %d has listed the content of current directory\n", term_pid);  
		exit(1);
	}

}
