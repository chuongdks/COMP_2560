#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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
		printf("Child %d sleeping...\n", getpid());
		sleep(4);
		exit(5); 
	}

	// Wait pid usage here in this example	
	while (waitpid(pid, &status, WNOHANG) == 0)
	{
		printf("still waiting...\n");
		sleep(1);
	}
	
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		printf("Exit status from %d was %d\n", pid, exit_status);
	}
	exit(0);
}
