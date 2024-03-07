#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>  

int main(){  
	int i, fd, pid;
	char c;

	pid = fork();

	if ((fd = open ("q2_test_1", O_RDWR|O_CREAT, 0644)) == -1) // Fork here
	{
		perror("test");
	}

	// pid = fork();

	dprintf (fd, "before fork, my pid is %d\n" , getpid());

	if ( pid == 0 ) // Child Process
	{
		dprintf(fd, "Hi, I am the Child. My pid is %d, myppid=%d\n", getpid(), getppid());
		dprintf(fd, "Child Process Closing the file now\n");
		close (fd);
	}
	else 
	{
		int inf = 3;
		while(inf > 0)
		{
			sleep(2);
			dprintf(fd, "Hi, I am the Parent. My pid is %d, myppid=%d. Loop number: %d\n", getpid(), getppid(), inf);
			inf--;
		}
		dprintf(fd, "Parent Process Closing the file now\n");
		close (fd);
	}
	//close (fd);
}


