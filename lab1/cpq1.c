#include <unistd.h> 
#include <fcntl.h>
#include <stdio.h>

//Program to read file1 and print a reverse string in file2
int main(int argc, char *argv[]){  
	int fd1;
	char buffer; // 1 character buffer  
	int fileSize=0;

	fd1 = open (argv[1], O_RDONLY); //open the file using read only

	//use lseek() to find the file size
	fileSize = lseek (fd1, 0, SEEK_END); //Offset from the beginning to the size of the file
 	printf ("File size is %d bytes\n", fileSize); //lseek return the number of offset it has done
	lseek (fd1, 0, SEEK_SET); //reset the offset back to the beginning by using SEEK_SET and set the 2nd parameter to 0


	close(fd1);  
}