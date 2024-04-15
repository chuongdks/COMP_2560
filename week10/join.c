#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
/*
	This program replicate the Bash script pipe. Ex: ls -l /usr/lib | more
*/
int join(char *com1[], char *com2[]) {

	int p[2], status;

	switch (fork()) 
	{
		case -1: 
			perror("1st fork call in join");
			exit(3);
		case 0: 
			break;
		default: 
			wait(&status);
			return(status);
	}
	
	// Child Process's code after breaking out of the switch statement
	if (pipe(p) == -1)
	{
		perror("pipecall in join ");
		exit(4);
	}

	switch (fork()) 
	{
		case -1:
			perror("2nd fork call failed in join");
			exit(5);
		case 0:  //the writing process (Grand Child proecss)
			// redirect stdout to the Write-end, means that stuff written to stdout is actually written to p[1]
			dup2(p[1], 1); 
				
			close(p[0]);
			close(p[1]);

			execvp(com1[0], com1);

			perror("1st execvp call failed in join");
			exit(6);
		default: // The "Parent" (Child) process's code
			// redireect stdin to the Read-end, means that stuff read from stdin is actually read from p[1], this part is necessary to make sure that com2 reads the output of com1
			dup2(p[0], 0); 

			close(p[0]);
			close(p[1]);

			// com2 will receive input from the pipe Read-end rather than the stdin
			/*
			This means that the standard input for the com2 command will be whatever is written to the pipe by the first command (com1). 
			Consequently, com2 will receive the output of com1 as its input.
			*/
			execvp(com2[0], com2); // the "more" cmd from com2, by default, will automatically read from stdin 

			perror("2nd execvp call failed in join");
			exit(7);
		}
}

int main (){

	char *one[4] = { "ls", "-l", "/usr/lib",NULL};
//	char *two[3]={"grep", "^d", NULL};

	char *two[2] = {"more", NULL};

	int ret;

	ret = join(one, two);

	printf("\n\njoin returned.\n");
	exit(0);
}



