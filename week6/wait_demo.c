#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int fatal(char *s) {
	perror(s);
	exit(1);
}


int main()
{
	pid_t pid;
	int status, exit_status;

	if ((pid = fork()) < 0)
		fatal("fork failed");
	if (pid == 0) 
	{
		sleep(4);
		exit(4); 
	}
	//      wait(NULL); what am I doing here?
	if ((pid = wait(&status)) == -1)
	{
		perror("wait failed");
		exit(2);
	}
	
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		printf("Exit status from %d was %d\n", pid, exit_status);
	}
	exit(0);
}

