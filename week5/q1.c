#include<stdio.h>
#include <unistd.h>

int main(){
	printf("before fork, my pid is %d\n" , getpid());  

	fork();

	fork();

	fork();

	printf("done, my pid is %d, my ppid=%d\n", getpid(), getppid());
}

