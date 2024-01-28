// reverse1.c
// solution 1: Start reading  at the end
//	Use lseek() on fileIn

#include <unistd.h> 
#include <fcntl.h>
#include <stdio.h>

//Program to read file1 and print a reverse string in file2
int main(int argc, char *argv[]){  
	int fd1, fd2;
	char buffer; // 1 character buffer  

	long int i=0, fileSize=0;

	fd1 = open (argv[1], O_RDONLY);
	fd2 = open (argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0755);

	// 2 ways to figure out the size of the file

	//First way, use read()
	// while (read (fd1, &buffer, 1) > 0)  
	// {
	// 	fileSize++;
	// 	//printf("files size is %d\n", fileSize);
	// }

	//Second way, use lseek()
	fileSize = lseek (fd1, 0, SEEK_END); //Offset from the beginning to the size of the file
 	printf ("files size is %d\n", fileSize); //lseek return the number of offset it has done
	lseek (fd1, 0, SEEK_SET); //reset the offset back to the beginning by using SEEK_SET and set the 2nd parameter to 0
	

	//loop start from i = 1 -> i = fileSize
	//This loop first offset the cursor to the second last position of the string
	//read 1 byte from fd1 and store it in buffer
	//write 1 byte to fd2 with content of buffer
	//Keep looping from End of the String to Start of the String to read in Reverse
	while(++i <= fileSize) // differnce between ++i and i++
	{  
		int lseekValue = lseek (fd1, -i, SEEK_END); 
		printf("The value of lseek is: %d\n", lseekValue); 
	    read (fd1, &buffer, 1);
		write (fd2, &buffer, 1);
	}

	close(fd1);  
	close(fd2);
}
