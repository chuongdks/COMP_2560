#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


int main(int argc, char *argv[]){  
	char buffer[100];
	int csd;  // Socket Descriptor for Client

	socklen_t len;
	struct sockaddr_in servAdd; // server socket address

	// 1. Socket
	csd = socket(AF_INET, SOCK_STREAM, 0);

	// Prepare server side address structure
	servAdd.sin_family = AF_INET;  
	servAdd.sin_addr.s_addr = inet_addr("137.207.82.51");  // ./test 137.207.82.53 or argv[1]
	servAdd.sin_port = 17777;  //change it to sth else?

	// 2. Connect
	int rt = connect(csd, (struct sockaddr *) &servAdd,  sizeof(servAdd));
	if (rt == -1)
	  	perror("connect() failed:");

	// Server and Client will send message back and forth
	while(1)
	{
		// 3. Read/Write
        // User enter a String
		fprintf(stderr, "Enter a line to send server\n");
		fgets(buffer, sizeof(buffer), stdin);
        // and send the buffer to the Server
		write(csd, buffer, sizeof(buffer));

        // Read from the server
		fprintf(stderr, "Waiting for Server’s message\n");  
		read(csd, buffer, sizeof(buffer));
		fprintf(stderr, "Server’s message is a reversed String: %s\n", buffer);          
	}
}

