//**************************************************************************************************************************************************
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

#define BUFSIZE 512

//This program Basically count how many characters in this file since 1 byte = 8 bits = 1 char
int main(int argc, char *argv[])
{
	char buffer[BUFSIZE];

	int fd;
	ssize_t nread;
	long total = 0;

	if ((fd = open ("filesize.c", O_RDONLY)) == -1)
	{
		printf("error in openning anotherfile\n");
		exit(1);
	}

	//read up to '512' bytes from 'fd' and store the read data into 'buffer'
    //return value is the number of byte actually read, if return 0 means it has reach EOF
    //for this loop, if n1 exceed 512, it will keep writing and concatinating until n1 = 0 ie reached EOF
	while ((nread = read (fd, buffer, BUFSIZE)) > 0)
	{
		total += nread; //increment total, basically read the number
	}

	printf("total chars in the file: %d\n", total);

	close(fd);
	exit(0);
}

