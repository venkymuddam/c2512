#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <vector>
#include <limits>

#define PORT 8080
#define BUFFER_SIZE 1024

int find_min(const std::vector<int>& numbers) {
    int min_value = std::numeric_limits<int>::max();
    for (int num : numbers) {
        if (num < min_value) {
            min_value = num;
        }
    }
    return min_value;
}

void run_server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    // Accept a connection
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Read data from client
    read(new_socket, buffer, BUFFER_SIZE);
    std::cout << "Received from client: " << buffer << std::endl;

    // Parse numbers and find the minimum
    std::stringstream ss(buffer);
    std::string token;
    std::vector<int> numbers;
    while (std::getline(ss, token, ',')) {
        numbers.push_back(std::stoi(token));
    }
    int min_value = find_min(numbers);

    // Send response to client
    std::string response = std::to_string(min_value);
    send(new_socket, response.c_str(), response.length(), 0);
    std::cout << "Minimum value sent to client: " << min_value << std::endl;

    // Close sockets
    close(new_socket);
    close(server_fd);
}

int main() {
    run_server();
    return 0;
}
