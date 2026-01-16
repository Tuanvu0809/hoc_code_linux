#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT_CONNECT 1028
#define DEVICE      5
#define BUFFER_SIZE 50

int main()
{
    printf("Serve Diagram\n");

    int server_fd;
    struct sockaddr_in server_address, client_address;
    socklen_t Client_len = sizeof(client_address);
    char Buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET , SOCK_DGRAM , 0 );

    if( server_fd < 0)
    {
        perror("fail creat serve socket \n");
        return 1;
    }

    printf("[SERVER] Socket created\n");

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT_CONNECT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if(bind(server_fd,(struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        perror("fail bind serve address\n");
        close(server_fd);
        return 1;
    }

    printf("[SERVER] Bound to port %d\n", PORT_CONNECT);

    while(1)
    {
        memset(Buffer,0,BUFFER_SIZE);
        int byte = recvfrom(server_fd, Buffer, BUFFER_SIZE, 0 , (struct sockaddr*) &client_address, &Client_len);

        if(byte > 0)
        {
            printf("[SERVER] Message: %s\n", Buffer);

            const char *response = "Message received!";
            sendto(server_fd, response, strlen(response), 0, (struct sockaddr*)&client_address, Client_len);
            printf("[SERVER] Response sent\n\n");
        }
    }
    close(server_fd);
    return 0;
}