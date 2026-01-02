#include <stdio.h>
#include <stdbool.h>
#include "../include/communicate.h"

extern char ip_address[IP_BUFFER_SIZE];
int g_client_fd = -1;
int g_server_fd = -1;
//extern bool Flag_check_blind = false;

int Serve_creat(uint16_t PORT_CONNECT)
{
    printf("Serve Stream \n") ; 
    //  int server_fd ; 
    int client_fd = -1;
    struct sockaddr_in serve_address, client_address;
    socklen_t Client_len = sizeof(client_address); 
    char buffer[BUFFER_SIZE];
    /*Serve */
    //Creat socket
    g_server_fd = socket(AF_INET,SOCK_STREAM,0);
    if( g_server_fd < 0)
    {
        //perror("fail creat serve socket \n");
        return 1;
    }
    
    printf("[SERVER] Socket created\n");
    memset(&serve_address, 0, sizeof(serve_address));
    serve_address.sin_family = AF_INET;
    serve_address.sin_port = htons(PORT_CONNECT);
    serve_address.sin_addr.s_addr = INADDR_ANY;
 
    if((bind(g_server_fd,(struct sockaddr*)&serve_address, sizeof(serve_address)) < 0)   )
    {
        perror("fail bind serve address\n");
        close(g_server_fd);
        
        return 1;
    }

    printf("[SERVER] Bound to port %d\n", PORT_CONNECT);
    //listen 
    if( listen(g_server_fd,DEVICE) < 0)
    {
        perror("fail listen\n");
        close(g_server_fd);
        return 1;
    }

    printf("wait client...\n");
    while(1){
        client_fd = accept(g_server_fd,(struct sockaddr*)&client_address,&Client_len);

        if (client_fd < 0) 
        {
            perror("accept failed");
            close(g_server_fd);
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
    }
        

    printf("[SERVER] Connection closed\n");
    return 0;
}

int Client_creat(uint16_t PORT_CONNECT , char *ip)
{
    // int g_client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    
    // 1. socket() - Create socket
   g_client_fd= socket(AF_INET, SOCK_STREAM, 0);
    if (g_client_fd< 0) {
        perror("socket failed");
        return 1;
    }
    printf("[CLIENT] Socket created\n");
    
    // 2. Setup server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT_CONNECT); // Host TO Network Short (16-bit, for port numbers)
    
    // Convert IP address, check IP address is valid or not
    if (inet_pton(AF_INET,  ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        close(g_client_fd);
        return 1;
    }
    
    // 3. connect() - Connect to server
    printf("[CLIENT] Connecting to server...\n");
    if (connect(g_client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        close(g_client_fd);
        return 1;
    }
    printf("[CLIENT] Connected to server\n");
    
    // 4. write() - Send data to server
    const char *message = "Hello I'm client!";
    write(g_client_fd, message, strlen(message));
    printf("[CLIENT] Sent: %s\n", message);
    
    // 5. read() - Receive response from server
    memset(buffer, 0, BUFFER_SIZE);
    int bytes_read = read(g_client_fd, buffer, BUFFER_SIZE);
    if (bytes_read > 0) {
        printf("[CLIENT] Received: %s\n", buffer);
    }
    
    // // 6. close() - Close connection
    close(g_client_fd);

    // printf("[CLIENT] Connection closed\n");
    return 0;
}

void Tcp_stream_disconnect()
{

    if (g_client_fd >= 0)
        shutdown(g_client_fd, SHUT_RDWR);

    if (g_server_fd >= 0)
        shutdown(g_server_fd, SHUT_RDWR);
}

void Tcp_stream_server(uint16_t PORT)
{
    if(Serve_creat(PORT) == 1)
    {
        fprintf(stderr,"connet fail!!\n");
        return ;

    }
}

void Tcp_stream_client(char *ip , uint16_t PORT)
{
    if(Client_creat(PORT,ip) == 1)
    {
        fprintf(stderr,"connet fail!!\n");
        return ;

    }
}