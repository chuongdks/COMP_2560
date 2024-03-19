/*
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

char msg[19];
int main(int argc, char *argv[]){  
	int fd, fdc;
	char ch;

	

	while((fd=open("/tmp/myserver", O_WRONLY))==-1){  //open to write to "myserver"
		fprintf(stderr, "trying to connect to myserver\n");  
		sleep(1);
	}
	
	sleep(2);
	
	while((fdc=open("/tmp/clientserver", O_RDONLY))==-1){//open to read from clientserver
		fprintf(stderr, "trying to connect to clientserver (for receiving response)\n");  
		sleep(1);
	}

	

	

	printf("client side:Connected both ways: type in data to be sent\n");  

	while(1) {
		while((ch=getchar()) != -1) {// -1 is CTRL-D
			write(fd, &ch, 1);
			printf("wrote ch:%d\n", ch);
			
			if(ch==10) {  // '\n'
				printf("I am reading msg.\n");
				read(fdc, msg, 18);
				printf("%s", msg);
			}  
		}
	}
	close(fd);
}
*/

//what does the above commented code do?

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){  
	int fd;
	char ch;
	
	while((fd=open("../myserver", O_WRONLY))==-1){  
		fprintf(stderr, "trying to connect\n");  
		sleep(1);
	}

	printf("Connected: type in data to be sent\n");  

	while((ch=getchar()) != -1) // -1 is CTRL-D
		write(fd, &ch, 1);  
	close(fd);
}


