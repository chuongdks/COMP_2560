#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>



int main(int argc, char *argv[]){  
	char buffer[100];
	int csd;  socklen_t len;
	
	struct sockaddr_in servAdd; //server socket address

	csd = socket(AF_INET, SOCK_STREAM, 0);

	servAdd.sin_family = AF_INET;  
	servAdd.sin_addr.s_addr = inet_addr(argv[1]);  
	servAdd.sin_port = 8777;

	int rt = connect(csd, (struct sockaddr *) &servAdd,  sizeof(servAdd));
	//fprintf(stderr, "rt=%d \n", rt);

	while(1){
		read(csd, buffer, 100);
		fprintf(stderr, "Server’s message: %s\n", buffer);  
		fprintf(stderr, "Enter a line to send server\n");
	
		//scanf is not the best choice here (why?), try fgets (...)  
		scanf("%s", buffer);
		//fgets(buffer, 100, stdin);

		if(buffer[0]=='$'){ 
                        close(csd);  
			exit(0);
		}
		write(csd, buffer, strlen(buffer)+1);
	}
}	


