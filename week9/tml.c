//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0
#define BELLS "\007\007\007"

int alarm_flag = FALSE;

void setflag(int sig) {
	alarm_flag = TRUE;
}

int main(int argc, char **argv) {
	int nsecs, j;
	pid_t pid;

//	static struct sigaction act;

	if (argc <= 2){
		fprintf(stderr, "Usuage: tml #minutes message\n");
		exit(1);
	}

	if ((nsecs = atoi(argv[1]) * 60) <= 0){
		fprintf(stderr, "tml: invalid time \n");
		exit(2);
	}
	
	switch (pid = fork()) {
		case -1: 
			perror("tml");
			exit(1);
		case 0: //child
			break;
		default: //parent
			printf("tml process-id %d\n", pid);
			exit(0);
	}
	

	signal(SIGALRM, setflag);

	alarm(nsecs);
	
	pause();

	if (alarm_flag == TRUE)	{
		printf(BELLS);
		for (j = 2; j < argc; j++)
			printf("%s ", argv[j]);
		printf("\n");
	}
	exit(0);
}



