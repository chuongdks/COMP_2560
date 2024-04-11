#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

//run this prg a few times to see how parent 
//and child process corrdinate with each other
// child write parent read (pcs2.c)

// Dummy function so that signal() will have something
void action(int dummy)
{
	sleep(1);
}  

void child(FILE *fp)
{  
	int value;

	while(1)
	{
		sleep(1);
		
		// Generate random number
		value = random()%100;  // 0 - 99
		printf("in child process, value=%d,\n", value);		

		// rewind file to the begining
		rewind(fp);

		// Write random number to the file pointer
		fwrite(&value, sizeof(int), 1, fp);  
		printf("Child: waiting for parent\n\n");  

		// when child receive SIGUSR1, do function action()
		signal(SIGUSR1, action);

		// send the SIGUSR1 signal to the parent
		kill(getppid(), SIGUSR1);  

		// waiting for signal
		pause();
	}
}

void parent(FILE *fp, pid_t pid)
{  
	int childRes, counter = 0;

	while(1)
	{
		// when parent receive SIGUSR1, do function action()
		signal(SIGUSR1, action);  

		// waiting for signal
		pause();  
		rewind(fp); // child and parent share the same file Offset, so reset it

		// Read random number from the file pointer
		fread(&childRes, sizeof(int), 1, fp);
		printf("\nParent: child result: %d\n", childRes);  

		// Parent Counter increased every loop until 5, then it will delete the file and terminate the prorgam
		if(++counter>5)
		{
			printf("Parent: work done, bye bye\n");  
			unlink("./ipoc.txt"); // Delete the file
			kill(0, SIGTERM); // Send actual kill signal to every processes of the calling process
		}

		// Send signal SIGUSR1 to the child
		printf("Parent: waiting for child\n\n");  
		kill(pid, SIGUSR1);
	}
}


int main(int argc, char *argv[]){  
	FILE *fp;
	pid_t pid;  
	int childRes;

	fp = fopen("./ipoc.txt", "w+");  
	setbuf(fp, NULL);

	if((pid=fork()) == 0)  
	{
		child(fp);
	}
	parent(fp, pid);
}






