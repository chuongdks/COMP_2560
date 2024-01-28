//ex2.c
#include <stdio.h>
#include <unistd.h>// This is needed for sleep() 

 int main(void){// forcing the flush with fflush
	int i=0;
	char line[100]="Hello, my name No-Name\n";  

	while(line[i] != '\0'){
		putchar(line[i++]);
		fflush(stdout);	// flush std output buffer  
		sleep(1);
	}
}

