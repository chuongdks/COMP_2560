#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netdb.h>
#include<stdlib.h>
#include<stdio.h>
#include<arpa/inet.h>

#define SIZE sizeof(struct sockaddr_in)

int main(){
	
    int sockfd;
	char c, rc;

	// Prepare server side address structure, done in 1 line /* convert and store the server's IP address */
    struct sockaddr_in server = { AF_INET, 7000 };
	
	//note the ip address, do this instead of typing in the ip address
    server.sin_addr.s_addr = inet_addr("137.207.82.53"); 
	
	// 1. Socket. Set up the transport end point
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket call failed");
		exit(1);
	}

	// 2. Connect the socket to the server's address  
	if (connect(sockfd, (struct sockaddr *)&server, SIZE) == -1)
	{
		perror("connect call failed");
	    exit(1);
	}

	// 3. Read/Write. Send and receive information from server 
	for (rc = '\n';;)
	{
		if (rc == '\n')
		{
			printf("input a lower case character\n");
		}

		c = getchar();
		send(sockfd, &c, 1, 0); // send a message on a socket, just like write() but with 'flag' argument at the end
		
		//receive a msg from socket, just like read() but with 'flag' argument at the end
		if (recv(sockfd, &rc, 1, 0) > 0)
		{
			printf("%c", rc);
		}
		else
		{
			printf("server has died\n");
			close(sockfd);
			exit(1);
		}
	}
}




