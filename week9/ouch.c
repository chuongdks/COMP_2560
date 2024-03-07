#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigHandler(int sig){
	printf("Ouch!\n");
}

int main(int argc, char *argv[]) {
	int j;
	
	if (signal(SIGINT, sigHandler) == SIG_ERR) {
		perror("signal");
		exit(4);
	}
	for (j = 0; ; j++) {
		printf("%d\n", j);
		sleep(3);   /* Loop slowly... */
	}
}
