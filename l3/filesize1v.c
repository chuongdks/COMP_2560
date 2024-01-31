//filesize1v.c
#include <stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]){  
	FILE *fd;
	
	unsigned char ch;  

	int fileSize=-1;

	fd = fopen(argv[1], "r"); 

	do{
		ch=getc(fd);  //0xFF
		fileSize++;
		//sleep(1);
			 
	} while( ch != EOF);  //ch =0x FF,  EOF=0x FFFF FFFF
	
	printf("Size of %s is %d\n", argv[1], fileSize);
}

