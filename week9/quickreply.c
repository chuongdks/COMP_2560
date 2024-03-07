
#include <stdio.h>
#include <signal.h>
#include<unistd.h>


#define TIMEOUT 5 
#define MAXTRIES 5 
#define LINESIZE 100 
#define CTRL_G '\007' 
#define TRUE 1
#define FALSE 0


//enter something from keyboard within 5 second, maximum 5 tries
//or....

static int timed_out;

static char answer[LINESIZE];

void catch (int sig){
	
	timed_out = TRUE;
	
	puts("hurry up, please enter to try again.\n");
}


char *quickreply(char *prompt){

	int ntries;

	signal(SIGALRM, catch);

	for (ntries = 0; ntries < MAXTRIES; ntries++) {
		timed_out = FALSE;

		printf("ntries=%d\n", ntries);
		printf("\n%s > ", prompt);
		
		alarm(TIMEOUT);
		
		fgets(answer, LINESIZE, stdin);
		
		alarm(0);
		
		if (!timed_out)
			break;
	}

	signal(SIGALRM, SIG_DFL);
	
	return (ntries == MAXTRIES ? ((char *)0) : answer);
}

int main(){
	
	printf(" your input is: %s\n", quickreply("Enter:"));
}


