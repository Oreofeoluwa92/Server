#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    int fd;
    const char* myfifo = "/tmp/myfifo";
    string s;
    char arr1[2048];

    // Open FIFO for write only
    fd = open(myfifo, O_WRONLY);
    if (argc == 1) {
        getline(cin, s);
    }
    else {
        s = string("RANGE ") + string(argv[1]) + " " + string(argv[2]);
    }

    // Write to the FIFO
    write(fd, s.c_str(), s.size());
        close(fd);
       

    // Open FIFO for read only
    fd = open(myfifo, O_RDONLY);

    // Read from FIFO
   read(fd, arr1, sizeof(arr1));
   

    // Print the received message
    printf("Server said: %s\n", arr1);
    close(fd);

    return 0;
}