#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

//run this prg a few times to see how parent 
//and child process corrdinate with each other
// child write parent read (pcs2.c)

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

		value = random()%100;  // 0 - 99
		printf("in child process, value=%d,\n", value);		

		rewind(fp);

		fwrite(&value, sizeof(int), 1, fp);  

		printf("Child: waiting for parent\n\n");  

		signal(SIGUSR1, action);

		kill(getppid(), SIGUSR1);  

		pause();
	}
}

void parent(FILE *fp, pid_t pid)
{  
	int childRes, n = 0;

	while(1)
	{
		signal(SIGUSR1, action);  

		pause();  
		rewind(fp); // child and parent share the same file Offset, so reset it

		fread(&childRes, sizeof(int), 1, fp);
  
		printf("\nParent: child result: %d\n", childRes);  

		if(++n>5)
		{
			printf("Parent: work done, bye bye\n");  
			unlink("./ipoc.txt"); // Delete the file
			kill(0, SIGTERM); // Send actual kill signal to every processes of the calling process
		}
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






