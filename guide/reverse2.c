//solution 2: start writing at end of file2 instead of scanning words at the end of file1 and write at the beginning of file2

#include <unistd.h> 
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int fd1, fd2;
	char buffer; // 1 character buffer  
	long int i=0, fileSize=0;
	//char	buf2[] = "ABCDEFGHIJ";

	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0755);

	while (read (fd1, &buffer, 1) > 0)
	{
		fileSize++;
	}  

	printf("The file size of fd1 is: %d\n", fileSize); 
		
	int lseekValue = lseek (fd2, fileSize-1, SEEK_SET); //pointer to end
	printf("The value of lseek is: %d\n", lseekValue); 
	lseek (fd1, 0, SEEK_SET);   //pointer to start 

	// if (write(fd2, buf2, 10) != 10)
	// {
	// 	perror("buf2 write error");
	// 	/* offset now = 16394 */
	// }
	
	while(++i <= fileSize)
	{
		read (fd1, &buffer, 1);
		int lseekValue = lseek (fd2, -i, SEEK_END);
		printf("The value of lseek is: %d\n", -i); 
		write (fd2, &buffer, 1);
	}
	close(fd1);  
	close(fd2);
}

// Explain visual for the while loop:
// f1:
// abcdef

// f2:
// _ _ _ _ _ 	(offset 5 chars in the beginning) 
// _ _ _ _ _ a	(code move to the end with SEEK_END and offset by -1 and then write 1 char from fd1)
// _ _ _ _ b	(code move to the end with SEEK_END and offset by -2 and then write 1 char from fd1)
// _ _ _ c b	(code move to the end with SEEK_END and offset by -3 and then write 1 char from fd1)
// _ _ d c b	(code move to the end with SEEK_END and offset by -4 and then write 1 char from fd1)
// _ e d c b	(code move to the end with SEEK_END and offset by -5 and then write 1 char from fd1)
// f e d c b	(code move to the end with SEEK_END and offset by -6 and then write 1 char from fd1)
