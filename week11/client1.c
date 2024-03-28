// This is the client part

#include <fcntl.h> 
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[]){ // Client  

	char ch, fifoName[100];
	int fd;  
    pid_t pid;

	while((fd=open("/tmp/sc2", O_WRONLY))==-1)
	{  
		fprintf(stderr, "trying to connect\n");  
		sleep(1);
	}

	// Get the pid and write it to the server side file
	pid = getpid();
	write(fd, &pid, sizeof(pid_t)); 
 
	// close the fd
	close(fd);  

	// store the new filename in the String "fifoName"
	sprintf(fifoName, "/tmp/fifo%ld", pid);  
	sleep(1);

	// Open the new file based on fifo Name that child function have already mkfifo() for
	fd = open(fifoName, O_RDONLY);  

	int ret = read(fd, &ch, 1); // Read from server side only 1 char?
	while(ret == 1) 
	{
		fprintf(stderr, "%c", ch);
		ret = read(fd, &ch, 1);
	}

	printf("ret = %d\n",ret);
	close(fd);
}

