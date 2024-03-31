#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

char msg[30];
int main(int argc, char *argv[]){  
	int fd, fdc;
	char ch;

	while((fd=open("/tmp/myserver", O_WRONLY)) == -1) // open to write to "myserver"
	{  
		fprintf(stderr, "trying to connect to myserver\n");  
		sleep(1);
	}
	
	// sleep(5); // 2 can play this game, 
	// In order to open a fifo file, one must open for READ and then the other open for WRITE
	
	while((fdc = open("/tmp/clientserver", O_RDONLY)) == -1) // open to read from clientserver
	{
		fprintf(stderr, "trying to connect to clientserver (for receiving response)\n");  
		sleep(1);
	}

	printf("client side: Connected both ways: type in data to be sent\n");  

	while(1) 
	{
		while((ch=getchar()) != -1)	// -1 is CTRL-D
		{
			write(fd, &ch, 1);
			printf("wrote ch: %d\n", ch);
			
			if(ch==10)	// ch = 10 is '\n' character, so everytime u pressed enter
			{  
				printf("I am reading msg From the Server.\n");
				read(fdc, msg, 30);
				printf("%s", msg);
			}  
		}
	}
	close(fd);
}
