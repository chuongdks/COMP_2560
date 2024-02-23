#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command1> <command2> ... <optional last command argument>\n", argv[0]);
        exit(1);
    }

    for (int i = 1; i < argc; i += 2) {
        pid_t pid;
        if ((pid = fork()) == -1) {
            perror("fork");
            exit(1);
        }

        if (pid == 0) 
        { // Child
            char *command = argv[i]; // Get the command
            char *arg[] = {command, argv[i+1], NULL}; // Arguments include the command and its argument
            execvp(command, arg); // Execute the command with its arguments
            perror("execvp failed"); // execvp only returns if an error occurs
            exit(1);
        } 
        else { // Parent
            int status;
            if (waitpid(pid, &status, 0) == -1)
            {
                perror("waitpid");
                exit(1);
            }
            if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) 
            {
                fprintf(stderr, "Command failed: %s\n", argv[i]);
                exit(1);
            }
        }
    }

    return 0;
}
