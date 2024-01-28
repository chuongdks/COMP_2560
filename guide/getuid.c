#include<unistd.h>
#include<sys/types.h>

#include <stdio.h> 

//int getuid();
int main(int argc, char * argv[]){
    printf("hello, my uid is %d\n",getuid());
//    getuid();
}

