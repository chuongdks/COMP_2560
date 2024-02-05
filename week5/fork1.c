//fork1.c

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){  
	int pid;

	printf("Only one process so far\n");  

	pid = fork();

	if(pid == -1){  
		perror("impossible to fork");  
		exit(1);
	}


	if(pid > 0) {
		printf("I am the parent, pid=%d\n", getpid());  
//		sleep(2);
	}
	else
		if(pid == 0) {
			printf("I am the child, pid=%d\n", getpid());
			//run this program a few more times to observe the output of the //
			//sentence below
			// printf("My parent's ID is , ppid=%d\n", getppid());
		}

	exit(0);
}

