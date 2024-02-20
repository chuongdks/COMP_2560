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

	// wait(NULL); what am I doing here? Dont belong here cuz there will be no variable to check exit status
	// First way to do wait, plz comment first way or second way
	if ((pid = wait(&status)) == -1) // exit statis is stored in status address = 4
	{
		perror("wait failed");
		exit(2);
	}

	// Second way to do wait, plz comment first way or second way
	while (waitpid(pid, &status, WNOHANG) == 0) 
	// exit statis is stored in status address = 4
	// NOHANG consant means that the parent process is not halted if no child is terminated, which means no child's pid returned
	{
		printf("still waiting...\n");
		sleep(1);
	}
	
	if (WIFEXITED(status)) // Return true if status was returned for a child that termminated normally, 
	// Could execute this code next: WEXITSTATUS(status) to fetch the low order 8 bits of the argument that the child passed to exit()
	// These MACRO replace what is done in the shifting bit parts of the program terminate2.c
	{
		exit_status = WEXITSTATUS(status);
		printf("Exit status from %d was %d\n", pid, exit_status);
	}
	exit(0);
}
