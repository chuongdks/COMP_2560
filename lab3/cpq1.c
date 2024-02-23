#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>

// PUT 2 MACRO WIFSIGNALED and WTERMSIG

int main() {  
	int newpid;
	
	printf("before: mypid is %d\n", getpid());  

	if ((newpid = fork()) == -1 )
	{
		perror("fork");  
	}
	else if (newpid == 0)
	{
		printf("I am the child %d now sleeping...\n",getpid());  
		sleep(5);
		abort();  //terminate abnormally, this program is almost the same as terminate2.c except this part it use abort() instead of exit()
	}
	else if (newpid > 0)
	{
		printf("I am the parent %d\n",getpid());  

		int status, exit_status;

		// wait(NULL); what am I doing here? Dont belong here cuz there will be no variable to check exit status
		if ((newpid = wait(&status)) == -1) // exit statis is stored in status address = 4
		{
			perror("wait failed");
			exit(2);
		}

		if (WIFSIGNALED(status)) // Return true if status was returned for a child that termminated normally, 
		{
			exit_status = WTERMSIG(status);
			printf("Exit status from %d was %d\n", newpid, exit_status);
		}
	}
}



