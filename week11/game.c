#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

//is the ramdon number genreated each time the same? fix?

void player(char *s, int *fd1, int *fd2);


int main(int argc, char *argv[]){ 

    int fd1[2], fd2[2], fd3[2], fd4[2];  
	// The "Token" can be anything: String, integrer, char,...
	char turn='T';

	printf("This is a 2-player game with a referee\n");  
	

	pipe(fd1);
	pipe(fd2);  


//identify parent code, child code
	if(!fork())  //one child process for player TOTO
    {
		player("TOTO", fd1, fd2);
	}


	close(fd1[0]);	// parent not read from fd1,( parent only write to pipe 1 )
	close(fd2[1]); 	// parent not write to fd2, ( parent only reads from pipe 2). 
                       //see my diagram posted
   //-------------------------------------------------------------------
	pipe(fd3);  
	pipe(fd4);  

	if(!fork())
	{
		player("TITI", fd3, fd4);
	}


	close(fd3[0]); // parent only write to pipe 3  
	close(fd4[1]);   // parent only reads from pipe 4

	// 
	while(1)
	{
		// Coordinate to Player 1 (Child 1)
		printf("\nReferee: TOTO plays\n\n");  
		write(fd1[1], &turn, 1);  //parent write to pipe 1, fd1
		// printf("TOTO Step 1\n");  // added by me

		// Parent process Stopped until it read somthing
		read(fd2[0],  &turn, 1);
		// printf("TOTO Step 4\n"); //added by me

		// Coordinate to Player 2 (Child 2)
		printf("\nReferee: TITI plays\n\n");  
		write(fd3[1], &turn, 1);
		// printf("TITI Step 1\n");  // added by me

		// Parent process Stopped until it read somthing
		read(fd4[0],  &turn, 1);   
		// printf("TITI Step 4\n"); //added by me
	}
}

void player(char *s, int *fd1, int *fd2){  

	int points=0;
	int dice;
	long int ss=0;  
	
	char turn;  
	close(fd1[1]);
	close(fd2[0]);  
	
	while(1)
	{
		read(fd1[0], &turn, 1);   //child read from pipe1 ,ie fd1
	//	printf("TOTO Step 2\n");  // added		

		// Random dice
		printf("%s: playing my dice\n", s);  
		dice = (int)time(&ss) % 10 + 1;  
		printf("%s: got %d points\n", s, dice); 
    	points+=dice;
		printf("%s: Total so far %d\n\n", s, points);  
		
		if(points >= 50)
		{
			printf("%s: game over I won\n", s); 
            kill(0, SIGTERM); // parameter 0 means send thr KILL signal to All
		}

		// 
		sleep(1);	// to slow down the execution  
		write(fd2[1], &turn, 1); //child write to pipe 2, ie fd2
//		printf("TOTO Step 3\n"); //added
	}
}
