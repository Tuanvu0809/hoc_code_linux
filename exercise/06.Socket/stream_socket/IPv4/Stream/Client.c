#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT_CONNECT 1028
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    
    // 1. socket() - Create socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("socket failed");
        return 1;
    }
    printf("[CLIENT] Socket created\n");
    
    // 2. Setup server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT_CONNECT); // Host TO Network Short (16-bit, for port numbers)
    
    // Convert IP address, check IP address is valid or not
    if (inet_pton(AF_INET,  "192.168.2.134", &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        close(client_fd);
        return 1;
    }
    
    // 3. connect() - Connect to server
    printf("[CLIENT] Connecting to server...\n");
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        close(client_fd);
        return 1;
    }
    printf("[CLIENT] Connected to server\n");
    
    // 4. write() - Send data to server
    const char *message = "Hello I'm client!";
    write(client_fd, message, strlen(message));
    printf("[CLIENT] Sent: %s\n", message);
    
    // 5. read() - Receive response from server
    memset(buffer, 0, BUFFER_SIZE);
    int bytes_read = read(client_fd, buffer, BUFFER_SIZE);
    if (bytes_read > 0) {
        printf("[CLIENT] Received: %s\n", buffer);
    }
    
    // 6. close() - Close connection
    close(client_fd);
    printf("[CLIENT] Connection closed\n");
    
    return 0;
}
