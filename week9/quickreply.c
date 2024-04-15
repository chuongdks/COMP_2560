#include <stdio.h>
#include <signal.h>
#include<unistd.h>

#define TIMEOUT 5 
#define MAXTRIES 5 
#define LINESIZE 100 
#define CTRL_G '\007' 
#define TRUE 1
#define FALSE 0

//enter something from keyboard within 5 second, or else complain to user, maximum 5 tries

static int timed_out;

static char answer[LINESIZE];

// catch() function when the alarm is activated after 5s, user took too long
void catch (int sig)
{
	timed_out = TRUE;
	puts("hurry up, please enter to try again.\n");
}

char *quickreply(char *prompt)
{
	int ntries; // Number of tries
	signal(SIGALRM, catch); // if SIGALARM is caught, use catch() function

	for (ntries = 0; ntries < MAXTRIES; ntries++) 
	{
		timed_out = FALSE;

		printf("ntries=%d\n", ntries);
		printf("\n%s > ", prompt);
		
		alarm(TIMEOUT); // User got 5 seconds to enter 

		fgets(answer, LINESIZE, stdin); // Use fgets to let uset enter
		alarm(0); // If user entered within 5s, then turn alarm to 0
		
		if (!timed_out)
			break;
	}

	signal(SIGALRM, SIG_DFL); // After 5 tries, revert back to the SIGALARM default action: Terminated
	
	return (ntries == MAXTRIES ? ((char *)0) : answer); // return user 'answer' if number of tries < MAXTRIES
}

int main(){
	printf(" your input is: %s\n", quickreply("Enter:"));
}


