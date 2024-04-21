#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>

int main(){
	int n=50, status;
	if(!fork())
		n=100;
	wait(&status);
	printf("%d\n", n);
	exit(0);
}

