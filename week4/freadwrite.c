#include <stdio.h>
#include <stdlib.h>

int main (int argc, char * argv[]) {

	FILE *f1;
	int data[10], i; 
        int data1[10];

	for(i=0; i<10; i++) 
		 data[i] = 10*i*i;
	
	if(!(f1=fopen(argv[1], "w"))){ 
		 printf("could not create file");  exit(1);
	}
	
	if(fwrite(data, sizeof(int), 10, f1) != 10){ 
		 printf("Error on writing into file");  
		exit(2);
	}
	fclose(f1);

	if(!(f1=fopen(argv[1], "r"))) {  
               printf("could open file");  
               exit(1);
        }
	if(fread(data1, sizeof(int), 10, f1) != 10)
        {  printf("Could not read data");
		exit(2);
       }
       
       for(i=0; i<10; i++)
         printf("reading data %d \n", data1[i]);
       fclose(f1);
}



