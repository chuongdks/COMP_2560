#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>  
#include <sys/wait.h>

int main(){  
	int i, fd, pid;

	// if ((fd = open ("q2_test", O_RDWR|O_CREAT, 0644)) == -1) // Fork here
	if ((fd = open ("q2_test", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) // Fork here
	{
		perror("test");
	}

	pid = fork();

	dprintf (fd, "Both process will run this line\n");

	if ( pid == 0 ) // Child Process
	{
		dprintf(fd, "Hi, I am the Child. My pid is %d, myppid=%d\n", getpid(), getppid());
		dprintf(fd, "Child Process Closing the file and then trapped in an infinite loop\n");
		close (fd); // Close the File Descriptor
		
		int inf = 0;
		while (inf == 0) // Trapped the child in an infinite loop
		{
			sleep(2);
			inf++;
		}
		exit(1);
	}
	else // Parent process
	{
		dprintf(fd, "Hi, I am the Parent. Waiting for my child number: %d to close the file\n", pid);
		wait(NULL); // Wait for the child to exit
		dprintf(fd, "Parent Process Closing the file now\n"); // Print to the file even after the child has closed the file descriptor
		close (fd); // CLose the file descriptor
	}
}


