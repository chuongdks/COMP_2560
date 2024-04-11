#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections */

/*
    Server listen to Client
    Client Send a msg to the Server 
    and the Server just sent back the msg it received to Client
*/

int main (int argc, char **argv) {
    int listenfd, connfd, n;
    socklen_t clilen;
    char buf[MAXLINE];

    struct sockaddr_in cliaddr, servaddr;

    // 1. Socketcreation of the socket
    listenfd = socket (AF_INET, SOCK_STREAM, 0);

    //preparation of the socket address, https://www.youtube.com/watch?v=bApd0QFsErU
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // htonl() convert to big-endian order
    servaddr.sin_port = htons(SERV_PORT);

    // 2. Bind
    bind (listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    // 3. Listen
    listen (listenfd, LISTENQ); // LISTENQ = 8
    printf("%s\n","Server running...waiting for connections.");

    for ( ; ; ) 
    {
        clilen = sizeof(cliaddr);

        // 4. Accept. Successful if client connect, return value is a Client Socket Descriptor
        connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);
        printf("%s\n","Received request...");

        // 5. Read/Write
        while ( (n = recv(connfd, buf, MAXLINE,0)) > 0) // receive a msg from socket, just like read() but with 'flag' argument at the end
        {
            printf("%s","String received from and resent to the client: ");
            puts(buf);
            send(connfd, buf, n, 0); // send a message on a socket, just like write() but with 'flag' argument at the end
        }

        if (n < 0) {
            perror("Read error");
            exit(1);
        }
        close(connfd);
    }
    
    //close listening socket
    close (listenfd);
}
