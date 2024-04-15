//*******************************
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* 
How to use:
./sendmessage "message 1 text"  "messgae 2 text"  ... 
*/

#define MSGSIZE 63

char *fifo = "fifo";

int main(int argc, char **argv) {
	int fd, j, nwrite;
	char msgbuf[MSGSIZE + 1];

	if (argc < 2)
	{
		fprintf(stderr, "usage: ./send message1 message 2 ....... \n");
		exit(1);
	}

	// Open fifo file for writing
	if ((fd = open(fifo, O_WRONLY|O_NONBLOCK )) < 0) // if delete O-NONBLOCK, Block if nobody open fifo other way |O_NONBLOCK 
	{  
		perror("fifo open failed");
		exit(4);
	}

	for (j = 1; j < argc; j++) //argv[0][1][2] -> argc = 3 (argc[0] is file name)
	{
		// Just checking size of msg
		if (strlen(argv[j]) > MSGSIZE)		
		{
			fprintf(stderr, "message too long %s\n", argv[j]);
			continue;
		}

		// Copy msg to var "msgbuf"
		strcpy(msgbuf, argv[j]);

		// Write to fifo
		if ((nwrite = write(fd, msgbuf, MSGSIZE + 1)) == -1) 
		{
			perror("message wirte failed");
			exit(5);
		}

		// Dont do the line below
		// read(fd, msgbuf, 100);
		// printf("Message is: %s", msgbuf);
	}
	close(fd);
	exit(0);
}


