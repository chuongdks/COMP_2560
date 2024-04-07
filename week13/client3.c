//**********************************************************************
//Client process
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
	
        struct sockaddr_in server = { AF_INET, 7000 };
	/* convert and store the server's IP address */
	
        server.sin_addr.s_addr = inet_addr("10.60.8.51"); 
//note the ip address 
	/* set up the transport end point */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket call failed");
		exit(1);
	}
	/* connect the socket to the server's address  */
	if (connect(sockfd, (struct sockaddr *)&server, SIZE) == -1){
		perror("connect call failed");
	        exit(1);
	}
	/* send and receive information from server */
	for (rc = '\n';;)
	{
		if (rc == '\n')
			printf("input a lower case character\n");
		c = getchar();
		send(sockfd, &c, 1, 0);
		
		if (recv(sockfd, &rc, 1, 0) > 0)
			printf("%c", rc);
		else{
			printf("server has died\n");
			close(sockfd);
			exit(1);
		}
	}
}




