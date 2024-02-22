#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>  

int main(){
	int pid, fd, i;  
    char c;

	if ( (fd =open("fork3_test",O_RDWR|O_CREAT, 0644)) == -1 )
	{  
		perror("test");
	}

	if( (pid = fork())< 0 )
	{
		perror("fork");  
		exit(1);
	}
	
	if(pid == 0) // child
	{
		for( i = 65; i < 85; i++) // ASCII A--> T
		{  
			c = i; 
			write(fd, &c ,1);
		}
	}
	else // parent 
	{    
		sleep(5); //The parent sleep for 5 secs, meanwhile the child write stuff, after that the parent write on it
		for( i = 0 ; i < 20; i++)
		{ 
			c = 64; // character @ spam 20 times
			write(fd, &c ,1);
		}
	}
		
	return 0;
}

