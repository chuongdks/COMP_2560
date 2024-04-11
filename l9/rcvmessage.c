//**************************************************************************************************************************************************
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define MSGSIZE 63

char *fifo = "fifo";

int main(int argc, char **argv){
	int fd;
	char msgbuf[MSGSIZE + 1];

    unlink(fifo);

	// Create fifo
	if (mkfifo(fifo, 0666) == -1)
	{
		if (errno != EEXIST) 
		{
			perror("receiver: mkfifo");
			exit(4);
		}
	}

	// Open fifo fd for READ n WRITE
	// Try putting it in the while loop like the sample server.c and client.c
	if ((fd = open(fifo, O_RDWR)) < 0) // note O_RDWR, change it to O_RDONLY?
	{   
		perror("fifo open failed");
		exit(5);
	}

	while(1) //for (;;) 
	{
		// Read the msg from the sendmessage.c file and store in msgubf
		int num = read(fd, msgbuf, MSGSIZE + 1);
		if (num < 0) 
		{
				perror("message read failed");
				exit(6);
		}

		// /* including the following when O_RDONLY */
		// if (num == 0) 
		// {
		// 	printf("nothing to read or no write end.\n");
		// 	// continue;
		// 	break;
		// } 	

		printf("message received:%s\n", msgbuf);

		// // Write the message back to the FIFO, dont do this, testing only
		// if (write(fd, "asdwdfuck", strlen(msgbuf) + 1) == -1) 
		// {
		// 	perror("message write failed");
		// 	exit(7);
		// }
	}
}


