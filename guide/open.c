#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

//This program is to create a new file
#define PERMS 0644 // permission for open with O_CREAT
char* filename = "newfile";

int main(int arge, char * argv[])
{
	int fileDescriptor;
	
	/*Open "anotherfile" read only*/
	//what if filename already exits, try O_EXCL

	if ((fileDescriptor = open (filename, O_RDWR|O_CREAT|O_EXCL, PERMS)) == -1)
	//if ((fileDescriptor = creat (filename, 0600)) < 0)
	{
		printf("could not create %s\n", filename);
		exit(1);
	}

	close(fileDescriptor);
	printf("done creating file, %d \n", fileDescriptor);
	exit(0);
}

