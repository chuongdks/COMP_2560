//client process
/*#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<stdlib.h>
#include<unistd.h>  */

#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>

#define SIZE sizeof(struct sockaddr_in)

int main() {
	int sockfd;
	char c;
	
	// Prepare server side address structure, done in 1 line
    /* the local port on the client */
	struct sockaddr_in client = { AF_INET, INADDR_ANY, INADDR_ANY };
	
    /* the remote address of the Server */
	struct sockaddr_in server = { AF_INET, 7000 };
	
    /* convert and store the Server's IP address */
	server.sin_addr.s_addr = inet_addr("137.207.82.53");

	// 1. Socket. Set up the transport end point 
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
		perror("socket call failed");
		exit(1);
	}

	// 2. Bind the local address to the end point. Usually, the client is suppose to connect() not bind()
	if (bind(sockfd, (struct sockaddr *)&client, SIZE) == -1){
		perror("bind call failed");
		exit(1);
	}

	// 5. Read/Write. Read a character from the keyborad */
	while (read(0, &c, 1) != 0)
	{
		/* send the charactor to the server */
		// sendto() has extra argument that needs the server socket descriptor so client4.c has it
		if (sendto(sockfd, &c, 1, 0, (struct sockaddr *)&server, SIZE) == -1)
		{
			perror("client: sending");
			continue;
		}

		/* receive the message back */
		if (recv(sockfd, &c, 1, 0) == -1)
		{
			perror("client: receiving");
			continue;
		}
		
		write(1, &c, 1);
	}
}

