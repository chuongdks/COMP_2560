// one possible solution

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define CHILD_DONE_SIGNAL SIGUSR1
// Signal handler function for handling signals sent by the child process
//3 marks + 1 mark for printf
void child_signal_handler(int signum) {
    if (signum == CHILD_DONE_SIGNAL) { //if comparison is not necessary
        printf("Child process has completed its task.\n");  //1 mark
    }
}

int main() {
    pid_t pid;

    // Set up signal handler for the parent process to handle signals sent by the child
    //2 marks
    signal(CHILD_DONE_SIGNAL, child_signal_handler);

    // Fork a child process
    //1 mark
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        // Task: Calculate factorial of 5
        //3 marks
        int factorial = 1;
        for (int i = 1; i <= 5; ++i) {
            factorial *= i;
        }
        //1 mark for printf below
        printf("Child process calculated factorial: %d\n", factorial);

        // Send signal to parent to indicate completion
       //2 marks
        kill(getppid(), CHILD_DONE_SIGNAL);
       //1 mark
        exit(EXIT_SUCCESS);
    } else { // Parent process
        // Wait for the child process to complete
        wait(NULL);  //1 mark
        //1 mark
        printf("Parent has successfully handled the signal from child and waited fro the child.\n");
    }

    return 0;
}

