#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netdb.h>
#include<stdlib.h>
#include<stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Server and Client will send message back and forth

void child(int sd);

int main(int argc, char *argv[]){ 
	char buffer[100];
	int sd, cd; // Socket Descriptor for Server and Client  
	socklen_t len;
	
	struct sockaddr_in servAdd, cliAdd; // server and client socket address  

	// 1. Socket
	sd = socket(AF_INET, SOCK_STREAM, 0);  

	// Prepare server side address structure
	servAdd.sin_family = AF_INET;  
	servAdd.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY doesnt need to know the IP address 
	servAdd.sin_port = 8777; // a port number
	
	// 2. Bind
	bind(sd,(struct sockaddr*)&servAdd,sizeof(servAdd));  

	// 3. Listen
	listen(sd, 5);

	while(1)
	{
		len = sizeof(cliAdd);

		// 4. Accept. Successful if client connect, return value is a Client Socket Descriptor
		cd = accept(sd, (struct sockaddr *) &cliAdd, &len); 
 
		//See the client's IP address using inet_ntoa()
		char *cli_addr = inet_ntoa(cliAdd.sin_addr);
		fprintf(stderr," Clinet connected from %s \n", cli_addr);

		// Fork and use the child process
		if(fork() == 0)
		{
			child(cd); 
		}
			 
		close(cd); // close the client Socket Descriptor
	}
}


void child(int cd) // The parameter is a Client Socket Descriptor
{  

	char line[255];

	// Server and Client will send message back and forth
	while(1)
	{
		fprintf(stderr, "Enter a line to send to client\n");  
		//scanf is not the best choice here (why?), scan word until space, while fgets scan until newline
		scanf("%s", line);

		//fgets(line, 255, stdin);		
		//fprintf(stderr,"line read: %s\n", line);

		// 5. Read/Write
		write(cd, line, strlen(line)+1);  

		// Once server write to the client, it use read() to wait for the client side
		if(!read(cd, line, 255))
		{  
			close(cd);
			exit(0);
		}
		fprintf(stderr, "Client sent back: %s\n", line);
	}
}
