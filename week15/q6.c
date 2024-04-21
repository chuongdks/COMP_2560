#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>

void action(){
	fprintf(stderr, "And ");
	exit(0);
}

int main(){
	if(!fork()){
		signal(SIGUSR1, action);
		fprintf(stderr, "Soup ");
		pause();
	}else{
		sleep(1);
		kill(getppid(), SIGUSR1);
		sleep(1);
	}
	fprintf(stderr, "Salad ");
}

