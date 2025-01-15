#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <sstream>

#define PORT 8080
#define BUFFER_SIZE 1024

void run_client() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Specify server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Get input from user
    std::string input;
    std::cout << "Enter numbers separated by commas (e.g., 10,20,30): ";
    std::getline(std::cin, input);

    // Send input to server
    send(sock, input.c_str(), input.length(), 0);
    std::cout << "Numbers sent to server" << std::endl;

    // Read response from server
    read(sock, buffer, BUFFER_SIZE);
    std::cout << "Minimum value from server: " << buffer << std::endl;

    // Close socket
    close(sock);
}

int main() {
    run_client();
    return 0;
}
