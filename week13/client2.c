#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[]){  
	char buffer[100];
	int csd;  socklen_t len; // Socket Descriptor for Client
	
	struct sockaddr_in servAdd; // server socket address

	// 1. Socket
	csd = socket(AF_INET, SOCK_STREAM, 0);

	// Prepare server side address structure
	servAdd.sin_family = AF_INET;  
	servAdd.sin_addr.s_addr = inet_addr(argv[1]);  // ./test 137.207.82.53
	servAdd.sin_port = 8777;

	// 2. Connect
	int rt = connect(csd, (struct sockaddr *) &servAdd,  sizeof(servAdd));
	//fprintf(stderr, "rt=%d \n", rt);

	// Server and Client will send message back and forth
	while(1)
	{
		// 3. Read/Write
		fprintf(stderr, "Waiting for Server’s message\n");  
		read(csd, buffer, 100);
		fprintf(stderr, "Server’s message: %s\n", buffer);  

		//scanf is not the best choice here (why?), try fgets (...)  
		fprintf(stderr, "Enter a line to send server\n");
		scanf("%s", buffer);
		//fgets(buffer, 100, stdin);

		if(buffer[0]=='$') // if user enter '$' on client side, close the client sd and exit the program
		{ 
            close(csd);  
			exit(0);
		}
		write(csd, buffer, strlen(buffer)+1);
	}
}	


