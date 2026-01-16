#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT_CONNECT 1028
#define DEVICE      5
#define BUFFER_SIZE 50


int main(){

    printf("Serve Stream \n"); 

    int server_fd , client_fd;
    struct sockaddr_in serve_address, client_address;
    socklen_t Client_len = sizeof(client_address); 
    char buffer[BUFFER_SIZE];

    /*Serve */
    //Creat socket
    server_fd = socket(AF_INET,SOCK_STREAM,0);
    if( server_fd < 0)
    {
        perror("fail creat serve socket \n");
        return 1;
    }
    
    printf("[SERVER] Socket created\n");

    //struct sockaddr_in server_addr;
    memset(&serve_address, 0, sizeof(serve_address));
    serve_address.sin_family = AF_INET;
    serve_address.sin_port = htons(PORT_CONNECT);
    serve_address.sin_addr.s_addr = INADDR_ANY;

    if(bind(server_fd,(struct sockaddr*)&serve_address, sizeof(serve_address)) < 0)
    {
        perror("fail bind serve address\n");
        close(server_fd);
        return 1;
    }

    printf("[SERVER] Bound to port %d\n", PORT_CONNECT);
    //listen 
    if( listen(server_fd,DEVICE) < 0)
    {
        perror("fail listen\n");
        close(server_fd);
        return 1;
    }

    // connect to client 

    printf("wait client...\n");
    
    client_fd = accept(server_fd,(struct sockaddr*)&client_address,&Client_len);

    if (client_fd < 0) 
    {
        perror("accept failed");
        close(server_fd);
        return 1;
    }
    printf("Listening...\n");


    printf("[SERVER] Client connected from %s:%d\n",
           inet_ntoa(client_address.sin_addr),
           ntohs(client_address.sin_port));
    
    // 5. read() - Receive data from client
    memset(buffer, 0, BUFFER_SIZE);
    int bytes_read = read(client_fd, buffer, BUFFER_SIZE);
    if (bytes_read > 0) {
        printf("[SERVER] Received: %s\n", buffer);
    }
    
    // 6. write() - Send response to client
    const char *response = "Hello I'm server!";
    write(client_fd, response, strlen(response));
    printf("[SERVER] Sent: %s\n", response);
    
    // 7. close() - Close connections
    close(client_fd);
    close(server_fd);
    printf("[SERVER] Connection closed\n");


   return 0;
}