#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void AlarmHandler(int dummy) // dummy will have the number 14
{ 
	static int n = 0;
	if(n++ < 3 )
	{  
		printf("Ding Ding Ding\n");		
		alarm(5);
	}
	else
		exit(0);
}

int main(int argc, char *argv[]){  
	alarm(5);
	signal(14, AlarmHandler); //what's the sig.no constant for 14

	while(1) 
	{
		int rt;
		rt=pause();
		printf("pause just returned , return value = %d \n", rt); // pauise return -1 if a signal is caught
    }
}


