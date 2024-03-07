#include <unistd.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void childFunction(char *line)
{
    // Print I am a child line
    printf("I am a child working for my parent\n");

    // Necessary Variable 
    int n1, n2, result; // arithamtic operation
    char op; // the operator
    char output[20] = ""; // String to store the arithmatic output
    
    // If the number of variable filled is not 3, return Wrong Statement case
    int argc = sscanf(line, "%d %c %d", &n1, &op, &n2);
    if (argc != 3) 
    {
        // Wrong statement, exit case 50
        exit(50);
    }

    // Switch case to do the calculaator
    switch (op) 
    {
        case '+':
            result = n1 + n2;
            break;
        case '-':
            result = n1 - n2;
            break;
        case '*':
            result = n1 * n2;
            break;
        case '/':
            if (n2 == 0) 
            {
                // Division by zero, exit case 100
                exit(100);
            }
            result = n1 / n2;
            break;
        default:
            // Wrong operator, exit case 200
            exit(200);
    }
    
    //Store the Formated Output in the String output
    sprintf(output, "%d %c %d = %d", n1, op, n2, result);
    printf("%s\n", output);
    exit(0);
}
int main(int argc, char *argv[])
{  
    while(1)
    {
        int pid, status, exit_status;
        char buffer[512] = ""; 

        printf("Enter  an  arithmetic  statement,  e.g.,  34  + 132 >\n");
        read (0, buffer, 512);

        // If process failed to fork
        if((pid = fork()) == -1)
        {  
            perror("impossible to fork");  
            exit(1);
        }
        
        // Parent process
        if (pid > 0) 
        {
            // printf("I am the parent, pid=%d\n", getpid());  

            // Wait for the child to terminate and take the exit status
            if (wait(&status) == -1)
            {
                perror("wait failed");
                exit(2);
            }
            
            // If the child process terminate successfully, use the MACRO
            if (WIFEXITED(status)) 
            {
                exit_status = WEXITSTATUS(status);

                //
                switch (exit_status) 
                {
                    case 0:
                        printf("Result above is correct\n");
                        break;
                    case 50:
                        printf("Wrong statement\n");
                        break;
                    case 100:
                        printf("Division by zero\n");
                        break;
                    case 200:
                        printf("Wrong operator\n");
                        break;
                }                
                // printf("Exit status from %d was %d\n", pid, exit_status);
            }
        }
        // Child process
        else if (pid == 0) 
        {
            // Do the calculator function
            childFunction(buffer);
        }
    }
}

