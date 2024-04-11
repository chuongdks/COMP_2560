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

/*
//  demo SIGPIPE, to demo, do not run ./server
void sigHandler(int sig){
	printf("Ouch!\n");
}*/

int main(int argc, char *argv[]){  
	char buffer[100];
	int csd;  // Socket Descriptor for Client

	socklen_t len;
	struct sockaddr_in servAdd; // server socket address

	// 1. Socket
	csd = socket(AF_INET, SOCK_STREAM, 0);

	// Prepare server side address structure
	servAdd.sin_family = AF_INET;  
	servAdd.sin_addr.s_addr = inet_addr(argv[1]);  // ./test 137.207.82.53
	servAdd.sin_port = 17777;  //change it to sth else?
	/*
	The inet_addr() function converts the specified string in the 
	Internet standard dot notation to an integer value suitable 
	for use as an Internet address.
	*/

	// 2. Connect
	int rt = connect(csd, (struct sockaddr *) &servAdd,  sizeof(servAdd));
	if (rt == -1)
	  	perror("connect() failed:");

	// 3. Read/Write
	read(csd, buffer, 100);

	fprintf(stderr, "%s\n", buffer);
}

