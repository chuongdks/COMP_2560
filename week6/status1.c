#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int fatal (char *s) 
{
	perror(s);
	exit(1);
}

int main()
{
	pid_t pid;
	int status, exit_status;

	if ((pid = fork()) < 0)
	{
		fatal("fork failed");
	}
		
	if (pid == 0) // Child Process
	{
		sleep(4);
		exit(5); 
	}

	if ((pid = wait(&status)) == -1)
	{
		perror("wait failed");
		exit(2);
	}

	//use macros	
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		printf("Exit status from %d was %d\n", pid, exit_status);
	}
	exit(0);
}

