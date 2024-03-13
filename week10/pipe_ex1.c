#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//please read these manual pages
//man 7 pipe , a very good read, 
//man read
//man 2 write


void child(int *);  
void parent(int *);

int main(int argc, char *argv[]){  
	int fd[2];

	if(pipe(fd) == -1)  
		exit(1);

	if(fork() == 0)  
		child(fd);
	else
		parent(fd);  
	exit(0);
}

//parent is the reader
void parent(int *fd){  
	char ch;

	close(fd[1]);
	printf("I am the parent process, the child process has sent the message:\n");  
	
	do{
		read(fd[0], &ch, 1);
		printf("%c", ch);  
		if(ch == '\n')
		    break;
	}while(1);
}

//child is the writer
void child(int *fd){

	char message[255]="Hello, here is my data...\n";

	close(fd[0]);  
	write(fd[1], message, 26);

}

