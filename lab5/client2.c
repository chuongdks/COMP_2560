#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_FILE "fifo_server_client"

int main() {
    int fd;
    char message[BUFSIZ];
    const char* prompt = "Enter a message: ";

    // Open FIFO for writing
    fd = open(FIFO_FILE, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("%s", prompt);
        fgets(message, BUFSIZ, stdin);

        // Write message to FIFO
        if (write(fd, message, strlen(message) + 1) == -1) {
            perror("write");
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Open FIFO for reading
        close(fd);  // Close write-only file descriptor
        fd = open(FIFO_FILE, O_RDONLY);  // Reopen for reading
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // Read acknowledgment from server
        if (read(fd, message, BUFSIZ) == -1) {
            perror("read");
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Print acknowledgment received from server
        printf("Acknowledgment from server: %s\n", message);

        // Close FIFO
        close(fd);

        // Reopen FIFO for writing
        fd = open(FIFO_FILE, O_WRONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
