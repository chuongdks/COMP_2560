// This is the server part

#include <wait.h>
#include <fcntl.h> 
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

//char fifoName[100];  

/*
void catcher(int c) 
{
	fprintf(stderr,"unlink fifo files\n");
	unlink("/tmp/sc1");
	unlink(fifoName);
	signal(SIGINT, SIG_DFL); // SIG_DFL: Default Handler
}
*/

void child(pid_t client);

int main(int argc, char *argv[]){  
	int fd, status;
	char ch;  pid_t pid;

	// signal(SIGINT, catcher);	

	unlink("/tmp/sc2");
	
	if(mkfifo("/tmp/sc2", 0777)){  
		perror("main");
		exit(1);
	}

	while(1)
	{
		fprintf(stderr, "Waiting for a client\n");  

		fd = open("/tmp/sc2", O_RDONLY);  
		fprintf(stderr, "Got a client: ");  
		read(fd, &pid, sizeof(pid_t)); // waiting to read the client pid
		close(fd);

		fprintf(stderr, "%ld\n", pid);  

		if(fork()==0)
		{
			// pass the pid of client to the child and child's function
			child(pid);
		}
		else  
		{
			waitpid(0, &status, WNOHANG);
			sleep(3);
			//printf("child pid=%d terminated.\n",wait(NULL)) ;
		}
	}
}

void child(pid_t pid)
{
	char fifoName[100];  
	char newline = '\n';  
	int fd, i;

	sprintf(fifoName,"/tmp/fifo%d", pid);  
	unlink(fifoName);
	mkfifo(fifoName, 0777);
	
	// Open the new file based on fifo Name that child function have already mkfifo() for
	fd = open(fifoName, O_WRONLY);  

	 // Write to client side a string of "fifoName" 10 times
	for(i = 0; i < 10; i++)
	{
		write(fd, fifoName, strlen(fifoName)); 
		write(fd, &newline, 1);
		sleep(1);
	}

	close(fd);  
	unlink(fifoName);  

	exit(0);
}


