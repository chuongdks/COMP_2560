#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>


#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/

int main(int argc, char **argv) {
    int sockfd; // Socket Descriptor for Client

    struct sockaddr_in servaddr; // server socket address

    char sendline[MAXLINE], recvline[MAXLINE];

    // basic check of the arguments, additional checks can be inserted
    if (argc !=2) {
        perror("Usage: TCPClient <IP address of the server");
        exit(1);
    }

    // 1. Socket. Create a socket for the client
    // If sockfd < 0 there was an error in the creation of the socket
    if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) 
    {
        perror("Problem in creating the socket");
        exit(2);
    }

    // Creation of the socket
    memset(&servaddr, 0, sizeof(servaddr)); // prof never do memset here, why now???
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr= inet_addr(argv[1]);
    servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order

    // 2. Connect. Connection of the client to the socket
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) 
    {
        perror("Problem in connecting to the server");
        exit(3);
    }

    // 3. Read/Write
    while (fgets(sendline, MAXLINE, stdin) != NULL) 
    {
        send(sockfd, sendline, strlen(sendline), 0); // send a message on a socket, just like write() but with 'flag' argument at the end

        if (recv(sockfd, recvline, MAXLINE,0) == 0) // receive a msg from socket, just like read() but with 'flag' argument at the end
        {
            //error: server terminated prematurely
            perror("The server terminated prematurely");
            exit(4);
        }
        
        printf("%s", "String received from the server: ");
        fputs(recvline, stdout);
    }

    exit(0);
}
