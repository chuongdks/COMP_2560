#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

//Buffer to hold the string
char	buf1[] = "abcdefghij";
char	buf2[] = "ABCDEFGHIJ";

int main(int argc, char * argv[])
{
	int fd;

	//this function is similar to: open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
	//Fild Descriptor 'fd' is declared by create()
	//The 'create()' function create a new file called "file.hole" with permission Read/Write for the owner only 0110 
	//return error if the 'fd' is <0 or = -1
	if ((fd = creat ("file.hole", 0600)) < 0)
	{
		perror("creat error");
	}
		
	//write to 'fd', write '10' bytes (10 characters) from 'buf1' which store the content to be written
	//return value of write() is the number of bytes actually written, return -1 if error occured
	if (write (fd, buf1, 10) != 10)
	{
		perror("buf1 write error");
		/* offset now = 10 */
	}

	//The purpose of this is to Move the File Offset (Creating a Hole)

	//• If 3rd argument is 'SEEK_SET', the file’s offset is set to offset bytes from the beginning of the file.
	//• If 3rd argument is 'SEEK_CUR', the file’s offset is set to its current value plus the offset. The offset can be positive or negative.
	//• If 3rd argument is 'SEEK_END', the file’s offset is set to the size of the file plus the offset.The offset can be positive or negative.

	//Since the 3rd argument "SEEK_SET" is used: Move the file 'fd' Offset to a position for 'offset' byte (2nd argument) from the start of the file
	//This creates a hole in the file, as the space between the initial write and the new write is not explicitly filled.
	//Imagine lseek like a cursor counting the number of byte it offset from specified places
	if (lseek(fd, 12, SEEK_SET) == -1) //16384
	{
		perror("lseek error");
		/* offset now = 16384 */
	}

	//WRite to file 'fd2' with buf2 content with only 10 bytes of data from buf2 (only 10 characters)
	if (write(fd, buf2, 10) != 10)
	{
		perror("buf2 write error");
		/* offset now = 16394 */
	}

	exit(0);
}

