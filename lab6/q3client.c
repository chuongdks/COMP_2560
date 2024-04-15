#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    char buffer[100];
    char *filename = "received_file.txt";
    FILE *file;

	// Prepare server side address structure, done in 1 line /* convert and store the server's IP address */
    struct sockaddr_in serv_addr = { AF_INET, 7000 };
	
	//note the ip address, do this instead of typing in the ip address
    serv_addr.sin_addr.s_addr = inet_addr("137.207.82.53"); 

    // 1. Socket. Set up the transport end point 
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
		perror("socket call failed");
		exit(1);
    }

    // 2. Connect the socket to the server's address  
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    {
		perror("connect call failed");
	    exit(1);
    }

    // 3. Read/Write. Send and receive information from server 
    recv(sockfd, buffer, sizeof(buffer), 0);
    printf("Server asked: %s", buffer);
    send(sockfd, "test.txt", strlen("test.txt"), 0); // Sending filename to Server
    
    // Open the file for Writing first
    file = fopen(filename, "w");
    if (file == NULL) 
    {
        perror("Error opening file");
        exit(1);
    }

    // Receiving file from server and saving it locally 
    while (recv(sockfd, buffer, sizeof(buffer), 0) > 0)
    {
        fputs (buffer, file);
    }

    fclose(file);
    printf("File received successfully\n");

    close(sockfd);
    return 0;
}
