#include <stdio.h>
#include <stddef.h>
#include <unistd.h>  // This is needed for sleep()  
#include <string.h>

//use your cell phone to count the second

int main(void){	// without fflush
	int i=0;
	char line[100]="Hello, my name No-Name\n";  
	printf("%d\n", strlen(line));   // 23
    printf("%d\n", sizeof(line));   // 100
	
	while(line[i] != '\0'){
	    putchar(line[i++]);  
	    sleep(1);
	   
	//   fflush(stdout);
	//    sleep(1);
        }
}



