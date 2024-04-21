#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>

void action(){
	fprintf(stderr, " Tuesday ");
	exit(100);
}

int main(){
	int st;
	if(fork()){
		alarm(1);
		signal(SIGALRM, action);
		sleep(2);
		fprintf(stderr, "exam ");
	}
	fprintf(stderr, " Friday ");
	wait(&st);
	fprintf(stderr, "%s\n", "done");
}

