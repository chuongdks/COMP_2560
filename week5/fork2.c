//fork2.c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int glb = 100; // global variable  

int main(){
	int pid;
	int var = 88;  // local variable for testing
	
	printf("before fork, my pid is %d\n" , getpid());  
	printf("Original value of glb: %d\nOriginal value of var: %d\n", glb, var);  
	pid = fork();
	if( pid < 0 ){  
		perror("fork");  
		exit(1);
	}

	//child  
	if(pid == 0)
	{ 
		glb++; var++;
		printf("I am the child, pid=%d\n", getpid());
		printf("My parent's ID is , ppid=%d\n", getppid());
		// sleep(10);
		// sleep(15);
	}
	else // parent
	{ 
		printf("I am the parent, pid=%d\n", getpid()); 
		// sleep(2);
	}
	
	printf("pid = %d, glob = %d, var = %d\n", getpid(), glb, var);
	return 0;
}


/*
main
{

  open a text file;
 int fd= open();

  fork();

	if(pid == 0){ //child  
	
		close(fd);
	}
	else{ // parent
		sleep(10);
	
		write sth to fd
		close();
		
		
	}


	}

}


cat file.text
*/
