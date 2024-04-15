#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>


// This is the server
int main(int argc, char *argv[]){  
	int fd, fdc;
	char ch;

	char *str = "I received your message\n";

	unlink("/tmp/myserver"); // delete it if it exists  
	if(mkfifo("/tmp/myserver", 0777)!=0)  //create FIFO for server to read
	{
		exit(1);
	}

    unlink("/tmp/clientserver"); // delete it if it exists  
	if(mkfifo("/tmp/clientserver", 0777)!=0) //create FIFO for client to write
	{
		exit(1);
	}

	fprintf(stderr, "Waiting for a client\n");  

	fd = open("/tmp/myserver", O_RDONLY);  // Server.c wait for Client.c to open for WRITE-Only
	fprintf(stderr, "Got a client (for reading): ");

	sleep(5); // Now Client Wait for Server to open fdc for WRITE-Only

	while((fdc = open("/tmp/clientserver", O_WRONLY)) == -1) // open FIFO for server(me) to write
	{  
		fprintf(stderr, "trying to connect to client\n");  
		sleep(1);
	}

	printf("server side: Connected both ways.\n");
  
	int t = strlen(str);
	printf("strlen(str) = %d\n", t);

	while(1)
	{
		// Reading content from client.c side
		while(read(fd, &ch, 1) == 1) 
		{
			fprintf(stderr, "%c\n", ch);

			// ch = 10 is '\n' character, so everytime u pressed enter
			// server.c will send the msg "str" to client.c for display
			if(ch==10) 
			{				
		        write(fdc, str, strlen(str));
				printf("wrote ch = %d\n", ch);			
			} 
		}
	}
}



