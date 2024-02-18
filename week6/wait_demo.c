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
		exit(69); 
	}

	// wait(NULL); what am I doing here? Dont belong here cuz there will be no variable to check exit status
	if ((pid = wait(&status)) == -1) // exit statis is stored in status address = 4
	{
		perror("wait failed");
		exit(2);
	}
	
	if (WIFEXITED(status)) // Return true if status was returned for a child that termminated normally, 
	// Could execute this code next: WEXITSTATUS(status) to fetch the low order 8 bits of the argument that the child passed to exit()
	{
		exit_status = WEXITSTATUS(status);
		printf("Exit status from %d was %d\n", pid, exit_status);
	}
	exit(0);
}

