#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

/*
	Server send Client a Message stored in String

	Socket has the same read/write relationship as pipe
	Where if one use read, it must wait for the others to write, etc
*/

int main(int argc, char *argv[]){
	char buffer[100] = "Hello, here is my message\n";  

	int sd, client; // Socket Descriptor for Server and Client
	socklen_t len;

	struct sockaddr_in servAdd; // server socket address  
	struct sockaddr_in cliAdd; // client socket address

	// 1. Socket
	sd = socket(AF_INET, SOCK_STREAM, 0);

	// Prepare server side address structure
	servAdd.sin_family = AF_INET;  
	servAdd.sin_addr.s_addr = inet_addr("137.207.82.53"); // Find ip using "ip addr" cmd, little helper function inet_addr
	servAdd.sin_port = 17777; // a port number
	// or use INADDR_ANY at sin_addr;
	/*
	INADDR_ANY allows your program to work without knowing the IP address 
	of the machine it was running on 
	*/

	//the following two statements were added in case port is not released by 
	//the kernal in a timely fashion when running the client many times.
	/*	
	int yes=1;
	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) 
	{
		perror("setsockopt");
		exit(1);
	}
	*/

	//all steps above are for calling bind.

	// 2. Bind
	int rt; //rt for gdb ti view returned value	
	rt = bind(sd, (struct sockaddr*) &servAdd, sizeof(servAdd));  

	// 3. Listen
	rt = listen(sd, 5); // Listen to 5 connection at a time

	while(1)
	{
		len = sizeof(cliAdd);

		// 4. Accept. Successful if client connect, return value is a Client Socket Descriptor
		client = accept(sd, (struct sockaddr*) &cliAdd, &len); 
        //accept (sd, NULL, NULL);

		// 5. Read/Write
		rt = write(client, buffer, strlen(buffer) + 1);  

		close(client); // close the client Socket Descriptor
		break;
	}
}


