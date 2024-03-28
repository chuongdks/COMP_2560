#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <signal.h>
#include <time.h>

void player(char *s, int fd1, int fd2);

int main(int argc, char *argv[]) {
    int fd1, fd2, fd3, fd4;
    char turn = 'T';

    printf("This is a 2-player game with a referee\n");

    // Delete fifo at the start
    unlink("fifo1");
    unlink("fifo2");
    unlink("fifo3");
    unlink("fifo4");

    // Create FIFOs
    if (mkfifo("fifo1", 0777) != 0 || 
        mkfifo("fifo2", 0777) != 0 || 
        mkfifo("fifo3", 0777) != 0 || 
        mkfifo("fifo4", 0777) != 0) 
    {
        exit(1);
    }

    // Open FIFOs
    fd1 = open("fifo1", O_RDWR);
    fd2 = open("fifo2", O_RDWR);
    fd3 = open("fifo3", O_RDWR);
    fd4 = open("fifo4", O_RDWR);

    // Fork child processes for players
    if (!fork()) 
    {
        player("TOTO", fd1, fd2);
    }

    if (!fork()) 
    {
        player("TITI", fd3, fd4);
    }

    while (1) 
    {
        // Coordinate to Player 1 (Child 1)
        printf("\nReferee: TOTO plays\n\n");
        write(fd1, &turn, 1);

        // Parent process waits for response from Player 1 (Child 1)
        read(fd2, &turn, 1);

        // Coordinate to Player 2 (Child 2)
        printf("\nReferee: TITI plays\n\n");
        write(fd3, &turn, 1);

        // Parent process waits for response from Player 2 (Child 2)
        read(fd4, &turn, 1);
    }

    return 0;
}

void player(char *s, int fd1, int fd2) 
{
    int points = 0;
    int dice;
    long int ss = 0;
    char turn;

    while (1) 
    {
        // Player reads its turn, waiting for the write end to send its token
        read(fd1, &turn, 1);

        // Random dice
        printf("%s: playing my dice\n", s);
        srand(time(NULL)); // Add this to randomzie more
        dice = ((int)time(&ss) % 5 + 1) + (rand() % 5 + 1);
        printf("%s: got %d points\n", s, dice);
        points += dice;
        printf("%s: Total so far %d\n\n", s, points);

        // Check if player has won
        if (points >= 50) 
        {
            printf("%s: game over I won\n", s);
            kill(0, SIGTERM); // parameter 0 means send thr KILL signal to All
        }

		sleep(1);	// to slow down the execution  

        // Player writes its turn back to the referee
        write(fd2, &turn, 1);
    }
}
