#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT_CONNECT 1028
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    socklen_t server_len = sizeof(server_addr);
    char buffer[BUFFER_SIZE];
    
    // 1. socket() - Create UDP socket
    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_fd < 0) {
        perror("socket failed");
        return 1;
    }
    printf("[CLIENT] UDP socket created\n");
    
    // 2. Setup server address (NO connect() needed!)
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT_CONNECT); // Host TO Network Short (16-bit, for port numbers)
   

    //Convert IP address, check IP address is valid or not
    if (inet_pton(AF_INET, "192.168.2.134", &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        close(client_fd);
        return 1;
    }
    
    // 3. sendto() - Send data (no connection!)
    const char *message = "Hello from UDP client!";
    sendto(client_fd, message, strlen(message), 0,(struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("[CLIENT] Sent: %s\n", message);
    
    // 4. recvfrom() - Receive response
    memset(buffer, 0, BUFFER_SIZE);
    int bytes = recvfrom(client_fd, buffer, BUFFER_SIZE, 0,(struct sockaddr*)&server_addr, &server_len);
    
    if (bytes > 0) {
        printf("[CLIENT] Received: %s\n", buffer);
    }
    
    // 5. close()
    close(client_fd);
    printf("[CLIENT] Socket closed\n");
    
    return 0;
}