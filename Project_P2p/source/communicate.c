#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/types.h>
#include <poll.h>
#include "../include/communicate.h"

extern info_socket_self self;
extern info_socket_connect *connect_socket;

extern command_t User_choice ; 

// extern int number_connection;
extern int number_connection ;

void poll_read_clients(info_socket_connect *clients, int *num_client)
{
    struct pollfd fds[MAX_CLIENT];
    char buffer[BUFFER_SIZE];

    /* 1. Setup pollfd */
    for (int i = 0; i < *num_client; i++) {
        fds[i].fd = clients[i].status;
        fds[i].events = POLLIN;
        fds[i].revents = 0;
    }

    /* 2. Gọi poll (block vô hạn) */
    int ready = poll(fds, *num_client, -1);
    if (ready < 0) {
        perror("poll");
        return;
    }

    /* 3.Check connect */
    for (int i = 0; i < *num_client; i++) {


        if (fds[i].revents & POLLIN) {

            int n = read(fds[i].fd, buffer, BUFFER_SIZE - 1);

            if (n > 0) {
                buffer[n] = '\0';
                printf("Client[%d]: %s\n", i, buffer);
            }
            // else if (n == 0) {
            //     printf("Client[%d] disconnected\n", i);
            //    // close(fds[i].fd);

            //     // /* Remove client */
            //     // clients[i] = clients[*num_client - 1];
            //     // (*num_client)--;

            //     // i--;  // check lại vị trí này
            // }
            else {
                perror("read");
            }
        }
    }
}


int Serve_creat(uint16_t PORT_CONNECT)
{
    printf("Serve Stream \n") ; 

    socklen_t connect_size = sizeof(struct sockaddr_in); 
    info_socket_connect *connect_other;
    
    char buffer[BUFFER_SIZE];
    connect_other = (info_socket_connect *)malloc(sizeof(info_socket_connect));

    connect_other->status = -1;

    if (!connect_other) {
        perror("malloc failed");
        return -1;
    }
    /*Serve */
    //Creat socket
    self.status_serve = socket(AF_INET,SOCK_STREAM,0);
    if( self.status_serve < 0)
    {
        //perror("fail creat serve socket \n");
        return 1;
    }
    
    printf("[SERVER] Socket created\n");
    memset(&self.address, 0, sizeof(self.address));
    self.address.sin_family = AF_INET;
    self.address.sin_port = htons(PORT_CONNECT);
    self.address.sin_addr.s_addr = INADDR_ANY;
 
    if((bind(self.status_serve,(struct sockaddr*)&self.address, sizeof(self.address)) < 0)   )
    {
        perror("fail bind serve address\n");
        close(self.status_serve);
        
        return 1;
    }

    printf("[SERVER] Bound to port %d\n", PORT_CONNECT);
    //listen 
    if( listen(self.status_serve,DEVICE) < 0)
    {
        perror("fail listen\n");
        close(self.status_serve);
        return 1;
    }

    printf("wait client...\n");
    while(1)
    {
        connect_other->status = accept(self.status_serve,(struct sockaddr*) &connect_other->address,&connect_size);

        if (connect_other->status < 0) 
        {
            perror("accept failed");
            close(self.status_serve);
            return 1;
        }
        printf("Listening...\n");
        /*save connect */
      
        connect_socket[number_connection] = *connect_other;
        number_connection ++;

  
        // 5. read() - Receive data from client
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_read = read(connect_other->status, buffer, BUFFER_SIZE);
        if (bytes_read > 0) {
            printf(" Received from : %s\n", buffer);
        }

        //  poll_read_clients(connect_socket,&number_connection);
        
        // // 6. write() - Send response to client
        // const char *response = "Hello I'm server!";
        // write(connect_other->status, response, strlen(response));
        // printf("[SERVER] Sent: %s\n", response);
        
        // 7. close() - Close connections
        //close(connect_other->status);
       
    }

    return 0;
}

int Client_creat(uint16_t PORT_CONNECT , char *ip)
{

    info_socket_connect *connect_other;
    char buffer[BUFFER_SIZE];

    /* malloc sockaddr_in */
    connect_other = (info_socket_connect *)malloc(sizeof(info_socket_connect));
    if (!connect_other) {
        perror("malloc failed");
        return -1;
    }

    // 1. socket() - Create socket
    self.status_client = socket(AF_INET, SOCK_STREAM, 0);
    if (self.status_client < 0) {
        perror("socket failed");
        free(connect_other);
        return -1;
    }
    printf("[CLIENT] Socket created\n");

    // 2. Setup server address
    memset(connect_other, 0, sizeof(struct sockaddr_in));
    connect_other->address.sin_family = AF_INET;
    connect_other->address.sin_port = htons(PORT_CONNECT);
    connect_other->status = -1;

    // server_address->sin_family = AF_INET;
    // server_address->sin_port   = htons(PORT_CONNECT);

    // Convert IP address
    if (inet_pton(AF_INET, ip, &connect_other->address.sin_addr) <= 0) {
        perror("Invalid address");
        close(self.status_client);
        free(connect_other);
        return -1;
    }

    // 3. connect() - Connect to server
    printf("[CLIENT] Connecting to server...\n");
    if (connect(self.status_client,  (struct sockaddr *) &connect_other->address,  sizeof(struct sockaddr_in)) < 0) {
        perror("connect failed");
        close(self.status_client);
        free(connect_other);
        return -1;
    }
    printf("[CLIENT] Connected to server\n");
    
    connect_other->status = self.status_client;
    connect_socket[number_connection] = *connect_other;
    number_connection ++;
    // 4. write() - Send data
    const char *message = "Hello I'm client!";
    if (write(self.status_client, message, strlen(message)) < 0) {
        perror("write failed");
    }
 
    // // 5. read() - Receive data
    // int bytes_read = read(self.status_client, buffer, BUFFER_SIZE - 1);
    // if (bytes_read > 0) {
    //     buffer[bytes_read] = '\0';
    //     printf("[CLIENT] Received: %s\n", buffer);
    // }

    // 6. close() - Close connection
    //close(self.status_client);
  
    free(connect_other);

    return 0;
}
void Send_message_to_connect(int index, const char *message)
{
    if (self.status_client < 0) {
        fprintf(stderr, "Socket not connected\n");
        return;
    }

    if (message == NULL) {
        fprintf(stderr, "Message is NULL\n");
        return;
    }

    size_t len = strlen(message);
    size_t sent = 0;

    while (sent < len) {
        ssize_t n = write(self.status_client,
                          message + sent,
                          len - sent);
        if (n < 0) {
            perror("write failed");
            return;
        }
        sent += n;
    }
}

void Tcp_stream_disconnect()
{

    if (self.status_client >= 0)
        shutdown(self.status_client, SHUT_RDWR);

    if (self.status_serve >= 0)
        shutdown(self.status_serve, SHUT_RDWR);
   
    if (connect_socket != NULL){    
        shutdown(connect_socket->status,SHUT_RDWR);
        free(connect_socket);
    }    
    
}

void Tcp_stream_server()
{
    if(Serve_creat(htons(self.address.sin_port)) == 1)
    {
        fprintf(stderr,"connet fail!!\n");
        return ;

    }

    close(self.status_serve);
    /*wait any mess in connect */
    poll_read_clients(connect_socket,&number_connection);
}

void Tcp_stream_client(char *ip , uint16_t PORT)
{

    
    if(Client_creat(PORT,ip) == 1)
    {
        fprintf(stderr,"connet fail!!\n");
        return ;

    }


    printf("\nConnect success, ready to send data \n");
}


void List_all_connect()
{
    printf("--------List all --------\n");
    // printf("serve:    %s   %d %d %s \n",inet_ntoa(self.address.sin_addr),htons(self.address.sin_port),self.status_client,connestatus > 0 ? "connect":"disconnect" );

    for(int i =0 ; i< number_connection ; i++)
    {
       printf("%d    %s   %d %d %s \n",i,inet_ntoa(connect_socket[i].address.sin_addr),htons(connect_socket[i].address.sin_port),connect_socket[i].status,connect_socket[i].status > 0 ? "connect":"disconnect" );
    
    }
    printf("-----------------------\n");
}


int malloc_socket() {
    connect_socket = malloc(sizeof(info_socket_self) * MAX_CLIENT);
    if (connect_socket == NULL) return 1;
    return 0;
}
