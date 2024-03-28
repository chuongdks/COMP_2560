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

    // Create FIFO
    mkfifo(FIFO_FILE, 0666);

    // Open FIFO for reading and writing
    fd = open(FIFO_FILE, O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Server started. Waiting for messages...\n");

    while (1) {
        // Read from FIFO
        if (read(fd, message, BUFSIZ) == -1) {
            perror("read");
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Print received message
        printf("Received message from client: %s\n", message);

        // Send acknowledgment back to client
        const char* ack_message = "I received your message\n";
        if (write(fd, ack_message, strlen(ack_message) + 1) == -1) 
        {
            perror("write");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    // Close FIFO
    close(fd);
    unlink(FIFO_FILE);

    return 0;
}
