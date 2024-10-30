#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

// Function to convert a string to uppercase
void toUpperCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    int fd;

    // FIFO file path (ensure it matches server path)
    char* myfifo = "/tmp/server_pipe";

    // Creating the named file (FIFO) if it doesn't exist
    mkfifo(myfifo, 0666);

    char arr1[80], arr2[80];

    // Prompt user for input
    printf("Enter range (format: RANGE XX YY): ");

    // Take input string from user, max length 80
    fgets(arr2, 80, stdin);

    // Convert command (first word) to uppercase for consistency
    char command[6];
    int lower, upper;
    if (sscanf(arr2, "%5s %d %d", command, &lower, &upper) == 3) {
        toUpperCase(command);
        snprintf(arr2, sizeof(arr2), "%s %d %d", command, lower, upper);
    }

    // Open FIFO for write only
    fd = open(myfifo, O_WRONLY);
    if (fd < 0) {
        perror("Error opening FIFO for writing");
        return 1;
    }

    // Write the input string to FIFO and close it
    write(fd, arr2, strlen(arr2) + 1);
    close(fd);

    // Open FIFO for read only
    fd = open(myfifo, O_RDONLY);
    if (fd < 0) {
        perror("Error opening FIFO for reading");
        return 1;
    }

    // Read the response from FIFO
    read(fd, arr1, sizeof(arr1));

    // Print the received message
    printf("Server response: %s\n", arr1);
    close(fd);

    return 0;
}
