#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{  
	int pid;
	pid = fork(); 

	if(pid == -1)
	{  
		perror("impossible to fork");  
		exit(1);
	}

	if(pid > 0) 
	{
		sleep(1);
		wait(NULL);
		printf("I am the parent, pid=%d\n", getpid());  
		
	}
	else if(pid == 0) 
	{
		int inf = 0;
		while (inf == 0)
		{
			sleep(1);
		}
		exit(1);
	}

	exit(0);
}

