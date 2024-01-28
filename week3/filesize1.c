//filesize1.c
#include <stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]){  
	FILE *fp;
	
	//unsigned char ch;  //what will happen if you uncomment this line and comment the 		
    char ch; //only compare up to -128,127 bits since it is a signed char by default; whatever u read, turn it into signed char

	int fileSize=-1;

	fp = fopen(argv[1], "r"); 

	do
	{
		ch = getc(fp);  //     0X  FF ,   ch =0X 00 00 00 FF, return unsigned char

		fileSize++;
		printf("fileSize=%d\n", fileSize);
		printf("Char read is ch=%c, in hex ch=%#hhx EOF is %#x\n\n", ch, ch, EOF); //if hex = 0xa: that char is "\n"
		sleep(1);
	} while( ch != EOF);  //ch =0x FF, EOF=0x FF FF FF FF 
 	 //   while(!feof(fd));

	printf(" \nout of do while loop now.\n\n");
	printf("ch=%d EOF=%#x\n", ch, EOF);
	printf("size of char =%ld size of EOF=%ld\n", sizeof(char), sizeof(EOF));
	
	printf("Size of %s is %d byte\n", argv[1], fileSize);
}





