#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netdb.h>
#include<stdlib.h>
#include<stdio.h>

#include <netinet/in.h>
#include <arpa/inet.h>


void child(int sd);


int main(int argc, char *argv[]){ 
	char buffer[100];
	int sd, cd;  
	socklen_t len;
	
	struct sockaddr_in servAdd, cliAdd;

	sd = socket(AF_INET, SOCK_STREAM, 0);  

	servAdd.sin_family = AF_INET;  
	servAdd.sin_addr.s_addr = INADDR_ANY;  
	servAdd.sin_port = 8777;
	
	bind(sd,(struct sockaddr*)&servAdd,sizeof(servAdd));  

	listen(sd, 5);

	while(1){
		len = sizeof(cliAdd);
		cd = accept(sd, (struct sockaddr *) &cliAdd, &len); 
 
		//in case you want to know the clicent's IP address.		
		char *cli_addr= inet_ntoa(cliAdd.sin_addr);
		fprintf(stderr," Clinet connected from %s \n", cli_addr);

		if(fork()==0)
			child(cd);  

		close(cd);
	}
}


void child(int cd){  

	char line[255];

	while(1){
		fprintf(stderr, "Enter a line to send to client\n");  
		//scanf is not the best choice here (why?), try fgets (...)
		scanf("%s", line);
		//fgets(line, 255, stdin);		
		//fprintf(stderr,"line read: %s\n", line);

		write(cd, line, strlen(line)+1);  
		if(!read(cd, line, 255)){  
			close(cd);
			exit(0);
		}
		fprintf(stderr, "Client sent back: %s\n", line);
	}
}
