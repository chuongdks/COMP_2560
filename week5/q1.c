#include<stdio.h>
#include <unistd.h>

int main(){
	printf("before fork, my pid is %d\n" , getpid());  
	//  Child process runs concurrently with the process that makes the fork() call (Parent process)
	fork(); // After child created, both parent and childs will execute the next instruction line 
	// P, C1
	// C1
	fork(); // Parent and Child 1 will create their own children
	// P, C1, C2
	// C1, C11
	// C11
	// C2
	fork(); 
	// P, C1, C2, C3
	// C1, C11, C12
	// C11, C111
	// C12
	// C111
	// C2, C21
	// C3
	// C21
	printf("done, my pid is %d, my ppid=%d\n", getpid(), getppid());
}

