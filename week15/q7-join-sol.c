//note students can totally rewrite the join(...) function
//based on a different but simalar logic.// for example
//create two child processes instead of one child , one //grandchild
#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int join(char *com1[], char *com2[]) {

	int p[2], status;

	switch (fork()) {
		case -1: 
			perror("1st fork call in join");
			exit(3);
		case 0: 
			break;
		default: 
			wait(&status);
			return(status);
	}
	
	//child process's code
        //1 mark
        unlink("/tmp/final");

       //2 marks, the name of the fifo is arbitrary
	if (mkfifo("/tmp/final", 0777) !=0){
		perror("problem create fifo ");
		exit(4);
	}


	switch (fork()) {
		case -1:
			perror("2nd fork call failed in join");
			exit(5);
		case 0:  //the writing process (grandchild procss)
                        //2 marks
			int fd= open("/tmp/final",O_WRONLY);
                        //1 mark
			dup2(fd, 1);  //redirect stdout to the pipe, writing end.
				
	//		close(p[0]);
	//		close(p[1]);
			close(fd);
            		execvp(com1[0], com1);

			perror("1st execvp call failed in join");
			exit(6);
		default: //the "parent" process's code
                        //2  marks
                        int fd2=open("/tmp/final", O_RDONLY);
                        //1 mark
			dup2(fd2, 0); //redirect stdin to the pipe, reading end

	//		close(p[0]);
	//		close(p[1]);
			close(fd2);
			execvp(com2[0], com2);

			perror("2nd execvp call failed in join");
			exit(7);
		}
}

int main (){

	char *one[4]={ "ls", "-l",NULL};

	char *two[2]={"more", NULL};

	int ret;

	ret=join(one, two);

	printf("\n\njoin returned.\n");
	exit(0);
}



