#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int fatal(char *s) {
	perror(s);
	exit(1);
}

int main(){
	pid_t pid;
	
	switch(pid=fork()) {

		case -1:
			fatal("fork failed");
			break;
		case 0:
			//child process
			execl("/bin/ls", "ls", "-l", (char *)0);
			fatal("exec failed");
			break;
		default: //parent process
			//wait((int *)0);
			wait(NULL);
			printf("ls completed.\n");
			exit(0);
	}
}

