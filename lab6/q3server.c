#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int sd, cd; // Socket Descriptor for Server and Client  
    
    char buffer[100];
    FILE *file;
    socklen_t len;

    struct sockaddr_in servAdd, cliAdd; // server and client socket address 

    // Prepare server side address structure
    servAdd.sin_family = AF_INET;
    servAdd.sin_addr.s_addr = INADDR_ANY;
    servAdd.sin_port = 7000;

    // 1. Socket
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
    {
		perror("socket call failed");
		exit(1);
    }

    // 2. Bind the local address to the end point 
    if (bind(sd, (struct sockaddr *)&servAdd, sizeof(servAdd)) == -1) 
    {
		perror("bind call failed");
		exit(1);
    }

    // 3. Listen. Start listening for incoming connection
    if (listen(sd, 5) == -1) 
    {
		perror("listen call failed");
		exit(1);
    }

    // 4. Accept. Successful if client connect, return value is a Client Socket Descriptor
    len = sizeof(cliAdd);
    if ((cd = accept(sd, (struct sockaddr *)&cliAdd, &len)) == -1) 
    {
		perror("accept call failed");
        exit(1);
    }

    // 5. Read/Write. Send and receive information from server 
    // Asking Client for filename
    send(cd, "What file do you want?\n", strlen("What file do you want?\n"), 0);
    recv(cd, buffer, sizeof(buffer), 0);
    printf("Client requested file: %s\n", buffer);

    // Sending file to client
    file = fopen(buffer, "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        exit(1);
    }
    
    fread(buffer, 1, sizeof(buffer), file);
    send(cd, buffer, sizeof(buffer), 0);

    fclose(file);
    printf("File sent successfully\n");

    close(cd);
    close(sd);
    return 0;
}
