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
#include<signal.h>

#define SIZE sizeof(struct sockaddr_in)

// Client use the Server to transform lower case character to Upper case

void catcher(int sig); //???

int newsockfd; // Gloval variable Client Socket Descriptor

int main()
{
	int sockfd;
	char c;

	// Prepare server side address structure, done in 1 line
	struct sockaddr_in server = { AF_INET, 7000, INADDR_ANY };

	// https://www.youtube.com/watch?v=bApd0QFsErU
	static struct sigaction act; 
	act.sa_handler = catcher;
	sigfillset(&(act.sa_mask));
	sigaction(SIGPIPE, &act, NULL);

	// 1. Socket. Set up the transport end point
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket call failed");
		exit(1);
	}

	// 2. Bind. Bbind an address to the end point 
	if (bind(sockfd, (struct sockaddr *)&server, SIZE) == -1)
	{
		perror("bind call failed");
		exit(1);
	}

	// 3. Listen. Start listening for incoming connection
	if (listen(sockfd, 5) == -1 )
	{
		perror("listen call failed");
		exit(1);
	}

	for (;;)
	{
		// 4. Accept. Successful if client connect, return value is a Client Socket Descriptor
		if ((newsockfd = accept(sockfd, NULL, NULL)) == -1)
		{
			perror("accept call failed");
			continue;
		}

		/* spawn a child do deal with the connection */
		if (fork() == 0)
		{
			// 5. Read/Write
			while (recv(newsockfd, &c, 1, 0) > 0) // receive a msg from socket, just like read() but with 'flag' argument at the end
			{
				c = toupper(c);
				send(newsockfd, &c, 1, 0); // send a message on a socket, just like write() but with 'flag' argument at the end
			}

			close(newsockfd);
			exit(0);
		}

		close(newsockfd);
	}
}

// https://www.youtube.com/watch?v=bApd0QFsErU
void catcher(int sig)
{
	close(newsockfd);
	exit(0);
}







