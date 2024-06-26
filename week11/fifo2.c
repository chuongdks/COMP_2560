// C program to implement one side of FIFO
// This side reads first, then writes
// One side Write the other read and vice versa
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int fd1;

	// FIFO file path
	char * myfifo = "myfifo";

	// Creating the named file(FIFO)
	// mkfifo(<pathname>,<permission>)
	mkfifo(myfifo, 0666);

	char str1[80], str2[80];
	while (1)
	{
		// First open in read only and read
		fd1 = open(myfifo, O_RDONLY);
		read(fd1, str1, 80);
		// Print the read string and close
		printf("User1: %s\n", str1);
		close(fd1);

		// Now open in write mode and write to fifo1.c
		fd1 = open(myfifo, O_WRONLY);
		fgets(str2, 80, stdin);
		write(fd1, str2, strlen(str2)+1);
		close(fd1);
	}
	return 0;
}
