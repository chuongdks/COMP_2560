#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

/*
    Rewrite game.c again, but this time use signals to achieve coordination between the
    referee and the two players.
*/

void player(char *s);

void player_handler(int dummy) 
{
	printf("Switching\n");
}

int main(int argc, char *argv[]) {
    printf("This is a 2-player game with a referee\n");

    pid_t player1PID, player2PID;

    // Fork Player 1
    if ((player1PID = fork()) == 0) 
    {
        player("TOTO");
        exit(0); // exit so child doesnt do more
    }

    // Fork Player 2
    if ((player2PID = fork()) == 0) 
    {
        player("TITI");
        exit(0); // exit so child doesnt do more
    }

    signal(SIGUSR1, player_handler);

    // Referee code
    while (1) 
    {
        // Coordinate to Player 1 (Child 1)
        printf("\nReferee: TOTO plays\n\n");
        kill(player1PID, SIGUSR1);
        pause(); // Parent process waits for response from Player 1 (Child 1)
    
        // Coordinate to Player 2 (Child 2)
        printf("\nReferee: TITI plays\n\n");
        kill(player2PID, SIGUSR1);
        pause(); // Parent process waits for response from Player 2 (Child 2)
    }

    return 0;
}

void player(char *s) {
    int points = 0;
    int dice;
    long int ss = 0;
    
    signal(SIGUSR1, player_handler);

    while (1) 
    {
        pause(); // Wait for referee (parent process) to send the kill() signal

        // Random dice better
        printf("%s: playing my dice\n", s);
        srand(time(NULL)); // Add this to randomzie more
        dice = ((int)time(&ss) % 3 + 1) + (rand() % 7 + 1);
        printf("%s: got %d points\n", s, dice);
        points += dice;
        printf("%s: Total so far %d\n\n", s, points);

        // Check if player has won
        if (points >= 50) 
        {
            printf("%s: game over I won\n", s);
            kill(0, SIGTERM); // Terminate all processes
        }

        sleep(1); // to slow down the execution

        // Player writes its turn back to the referee
        kill(getppid(), SIGUSR1);
    }
}
