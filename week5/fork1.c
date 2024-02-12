//fork1.c

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{  
	int pid;

	printf("Only one process so far\n");  

	//Make 2 process, which will run first? Up to kernel to decide
	printf("before fork, my pid is %d\n" , getpid());  
	pid = fork(); //parent process will return positive value with 2 process
	// printf("pid: %d\n", pid);  

	if(pid == -1){  
		perror("impossible to fork");  
		exit(1);
	}

	if(pid > 0) 
	{
	    sleep(2);
		printf("pid: %d\n", pid); 
		printf("I am the parent, pid=%d\n", getpid());  
		
	}
	else if(pid == 0) 
	{
	    //sleep(2);
		printf("pid: %d\n", pid); 
		printf("I am the child, pid=%d\n", getpid());
		//run this program a few more times to observe the output of the //
		//sentence below
		printf("My parent's ID is , ppid=%d\n", getppid());
	}

	//Testing
	//for (int i = 0; i <2; i++)
	//{
		//printf("%d");
	//}
	exit(0);
}

