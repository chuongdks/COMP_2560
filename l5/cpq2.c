#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>  

int main(){  
	int i, fd;
	char c;

	if ((fd = open ("q2_test", O_RDWR|O_CREAT, 0644)) == -1)
	{
		perror("test");
	}

	dprintf (fd, "before fork, my pid is %d\n" , getpid());

	for (i=0; i<3; i++)
 	{
		if ( fork() == 0 ) // If this is a child
		{
			dprintf(fd, "Hi, I am child. My pid is %d, myppid=%d\n", getpid(), getppid());
			break; // Keep the child from escaping this function block. 
		}
	}
	
	close (fd);
}

