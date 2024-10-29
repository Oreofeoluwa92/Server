#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<cmath>


typedef std::vector<int>vec;
using namespace std;


#define PIPE_NAME "/tmp/server_pipe"


// Function to check if a number is prime
bool Prime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;  // 2 is prime
    if (num % 2 == 0) return false;  // even numbers > 2 are not prime

    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}
//function to take prime range
vec find_primes(int lower, int upper) {
    vec primes;
    for (int num = lower; num <= upper; ++num) {
        if (Prime(num)) {
            primes.push_back(num);
        }
    }
    return primes;
}

// Main server function
int main() {
    // Create the named pipe
    mkfifo(PIPE_NAME, 0666);
    cout << "Server started, listening on " << PIPE_NAME << std::endl;

    char buffer[256];
    while (true) {
        // Open the pipe for reading
        int pipe_fd = open(PIPE_NAME, O_RDONLY);
        if (pipe_fd < 0) {
            cerr << "Error opening pipe for reading." << std::endl;
            return 1;
        }

        // Read the request
        ssize_t bytesRead = read(pipe_fd, buffer, sizeof(buffer) - 1);
        buffer[bytesRead] = '\0';  // Null-terminate the string

        close(pipe_fd);  // Close reading end

        // Parse the request
        std::istringstream iss(buffer);
        std::string command;
        int lower, upper;
        iss >> command >> lower >> upper;

        std::string response;
        if (command == "RANGE" && !iss.fail() && lower < upper) {
            // Calculate primes in the range
            vec primes = find_primes(lower, upper);
            std::ostringstream oss;
            for (auto prime : primes) {
                oss << prime << " ";
            }
            response = oss.str();
            if (response.empty()) {
                response = "No primes in this range.";
            }
        }
        else {
            response = "Malformed request";
        }

        // Write the response
        pipe_fd = open(PIPE_NAME, O_WRONLY);
        if (pipe_fd < 0) {
            std::cerr << "Error opening pipe for writing." << std::endl;
            return 1;
        }
        write(pipe_fd, response.c_str(), response.size() + 1);  // +1 to include null terminator
        close(pipe_fd);  // Close writing end

        std::cout << "Processed request: " << buffer << std::endl;
        std::cout << "Response sent: " << response << std::endl;
    }

    // Cleanup (this line will not be reached due to the infinite loop)
    unlink(PIPE_NAME);
    return 0;
}

