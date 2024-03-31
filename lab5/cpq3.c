#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void sigpipe_handler(int signum) {
    printf("Caught the SIGPIPE signal\n");
}

int main() {
    int pipe_fd[2], error;

    // Create pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Close read-end of the pipe
    close(pipe_fd[0]);

    // Install SIGPIPE signal handler
    signal(SIGPIPE, sigpipe_handler);

    // Write to the pipe
    if ((error = write(pipe_fd[1], "Hi", 3)) == -1) 
    {
        printf("write function return %d\n", error);
        perror("pipe problem");
    }

    // Close write-end of the pipe
    close(pipe_fd[1]);

    return 0;
}
