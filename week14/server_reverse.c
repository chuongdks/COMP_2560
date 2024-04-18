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
	Client send a string for Server to reverse it and then Server send the reversed String back to client
*/

// How to reverse a string: https://www.javatpoint.com/reverse-a-string-in-c
void reverseString(char *str) 
{
    int i, j;
    char temp;
    int length = strlen(str);
	int right = length - 1;

    for (i = 0; i < right; i++) 
	{
        temp = str[i];
        str[i] = str[right];
        str[right] = temp;
		right--;
    }
}

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
	servAdd.sin_addr.s_addr = inet_addr("137.207.82.51"); // Find ip using "ip addr" cmd, little helper function inet_addr
	servAdd.sin_port = 17777; // a port number

	//all steps above are for calling bind.

	// 2. Bind
	int rt; //rt for gdb ti view returned value	
	rt = bind(sd, (struct sockaddr*) &servAdd, sizeof(servAdd));  

	// 3. Listen
	rt = listen(sd, 5); // Listen to 5 connection at a time

	// while(1) { // Add this line and delete the while(1) below if u want to loop the accep() client part
		len = sizeof(cliAdd);

		// 4. Accept. Successful if client connect, return value is a Client Socket Descriptor
		client = accept(sd, (struct sockaddr*) &cliAdd, &len); 
	while(1)
	{
		// 5. Read/Write
		read(client, buffer, sizeof(buffer));  
        printf("Received message from client: %s\n", buffer);

        reverseString(buffer);

        write(client, buffer, sizeof(buffer));  
        printf("Reversed message sent to client: %s\n", buffer);
	}
}


