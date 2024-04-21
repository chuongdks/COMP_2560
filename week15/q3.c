#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

int main (){
	int i, status ;

	pid_t pid;

	for (i =0;i <4; i ++){
		pid=fork();
		if(pid == 0){ /* child */
			printf("Child : %d: Hello World !\n", i);
			exit(0);
		} else {
			/* parent */
			printf (" Parent : %d: Hello World !\n",i);	
		}
	}
	wait(&status);
	waitpid(-1, NULL, 0);

	sleep(2);
	return 0;
}
