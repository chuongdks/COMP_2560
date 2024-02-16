#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {  int pid;
printf("Before: process id %d\n",getpid());

if ((pid = fork())==0){
printf("I am the child %d\n",getpid());  sleep(5);
printf("Listing content of current directory...\n");
char* arg_list[3] = { "ls","-l", (char *)0}; //"ls",
// OR
// char* arg_list[3];
// arg_list[0] = "ls";
// arg_list[1] = "-l";
// arg_list[2] = 0;

execvp("/bin/ls",arg_list);
}
else{
printf("I am the parent %d\n", getpid());  int status;
int term_pid = wait(&status);
printf("Child %d has listed the content of current directory\n", term_pid);  exit(1);
}
}
