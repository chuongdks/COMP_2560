#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    int cpid1 = fork(); // this guy got fork() once by OG
    int cpid2 = fork(); //This guy got fork() 2 times, one by the OG and one the OG's child

    if(cpid1 != 0 && cpid2 != 0) // The OG case passing through 2 fork()
    {
        int status;
        printf("\nParent: I am going to wait for process with ID: %d\n", cpid2);
            
        // wait for any child to exit    
        // int waitPID = wait(&status); // is similar to: waitpid(-1, &status, 0);

        // wait for cpid2 to exit, comment line above and uncomment line below to execute
        int waitPID = waitpid (cpid2, &status, WUNTRACED);  // The third argument has lots of options, but usually just use '0' as default

        printf("\nParent: Waited for child, return value of waitpid(): %d\n", waitPID);
        printf("\nParent: Exit code of terminated child: %d\n", WEXITSTATUS(status));
        exit(1);
    }
    else if (cpid1 == 0 && cpid2 != 0) //OG's child passing 2nd fork, making a new child
    {
        printf("\nChild1: My process ID: %d, my exit code is 1 and my parent ID is: %d\n", getpid(), getppid());
        sleep(1);
        exit(1);   
    }
    else if (cpid1 != 0 && cpid2 == 0) //OG's second child case
    {
        printf("\nChild2: My process ID: %d, my exit code is 2 and my parent ID is: %d\n", getpid(), getppid());
        sleep(1);
        exit(2);
    }
    else if (cpid1 == 0 && cpid2 == 0) // OG's first child getting a child case, has a former child badge as cpid1 == 0
    {
        printf("\nChild3: My process ID: %d, my exit code is 3 and my parent ID is: %d\n", getpid(), getppid());
        sleep(1);
        exit(3);
    }

    return 0;
}