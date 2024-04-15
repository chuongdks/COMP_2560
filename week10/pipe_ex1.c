#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void child(int *);  
void parent(int *);

int main(int argc, char *argv[]){  
	int fd[2]; // fd[0] is the Pipe Read-end, fd[1] is the Pipe Write-End

	if(fork() == 0)  
		child(fd);
	else
		parent(fd);  
	exit(0);
}

//parent is the reader
void parent(int *fd){  
	char ch;

	close(fd[1]); // Close the Write-End since Parent is the Reader
	printf("I am the parent process, the child process has sent the message:\n");  
	
	do{
		read(fd[0], &ch, 1); // Read from the Read-end
		printf("%c", ch);  
		if(ch == '\n')
		    break;
	}while(1);
}

//child is the writer
void child(int *fd){

	char message[255]="Hello, here is my data...\n";

	close(fd[0]); // Close the Read-End since Child is the Writer
	write(fd[1], message, 26);

}

