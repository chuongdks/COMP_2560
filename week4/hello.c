#include <stdio.h>
#include <unistd.h>

int main() {


     //	printf("Hello world!");
	//printf("Hello world!\n");
      //  sleep(5);

	
	printf("To man the world is twofold"); //store in buffer
	sleep(2);
	write(STDOUT_FILENO, "in accordance with his twofold attitude.\n", 41); //flush by using '\n'


	printf("hi \n");
	sleep(2);

}
