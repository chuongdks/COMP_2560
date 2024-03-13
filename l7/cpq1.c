#include <stdio.h>
#include <string.h>
#include <signal.h>

int main() {
    // Example usage of strsignal
    for(int i = 0; i < 100; i++)
    {
        int signum = i;
        printf("Signal %d: %s\n", signum, strsignal(signum));
    }
    return 0;
}