#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int pid;

    if (argc < 2) 
    {
        fprintf(stderr, "Usage: %s <command1> <command2> ... <optional last command argument>\n", argv[0]);
        exit(1);
    }

    // Loop through all the arguments
    for (int i = 1; i < argc; i+=2) 
    {
        if((pid = fork()) == -1)
        {  
            perror("Impossible to fork");  
            exit(1);
        }
        
        //
        if (pid > 0) 
        {
            int status, exit_status;
            printf("\nThis cmd parent process pid is: %d\n", getppid());

            if (waitpid(pid, &status, 0) == -1)
            {
                perror("waitpid");
                exit(1);
            }

            if (WIFEXITED(status)) 
            {
                exit_status = WEXITSTATUS(status);
                printf("Exit status from the child process: %d was %d\n", pid, exit_status);
            }
        }
        else if (pid == 0) // Child
        {
            char *arg[] = {argv[i], argv[i+1], NULL};
            execvp (argv[i], arg);
            exit(47);
        }
    }
	
	return 0;
}