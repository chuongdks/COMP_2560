#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int docommand(char *command) {
	pid_t pid;
	
	if((pid=fork())<0)
	     return -1;

	if (pid==0){ /*child*/
	    execl("/bin/bash", "bash", "-c", command, (char*)0);
	    perror("excel");
            exit(1);
	}
p
	//code for parent
	wait((int *)0);
	return 0;
}

int main(){
	docommand("ls -lt"); //try change the paremeter to other commands
	
}
