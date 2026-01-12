#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/types.h>
#include "../include/communicate.h"

extern info_socket_self self;
extern info_socket_client *connect_socket;

extern command_t User_choice ; 

extern int number_connection;



int Serve_creat(uint16_t PORT_CONNECT)
{
    printf("Serve Stream \n") ; 
    //  int server_fd ; 
    int client_fd = -1;
    struct sockaddr_in *client_address;
    client_address = (struct sockaddr_in *) malloc (sizeof(struct sockaddr_in ));
    socklen_t Client_len = sizeof(client_address); 
    char buffer[BUFFER_SIZE];
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
    while(1){
        client_fd = accept(self.status_serve,(struct sockaddr*)&client_address,&Client_len);

        if (client_fd < 0) 
        {
            perror("accept failed");
            close(self.status_serve);
            return 1;
        }
        printf("Listening...\n");


        printf("[SERVER] Client connected from %s:%d\n",
            inet_ntoa(client_address->sin_addr),
            ntohs(client_address->sin_port));

        // connect_socket[number_connection].address = *client_address;
        // connect_socket[number_connection].status_client = client_fd;
        // number_connection ++;
        
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
    struct sockaddr_in *server_address;
    server_address = (struct sockaddr_in *) malloc (sizeof(struct sockaddr_in ));
    char buffer[BUFFER_SIZE];

    printf("\n ip và port %s %d", ip, PORT_CONNECT);
    
    // 1. socket() - Create socket
   self.status_client= socket(AF_INET, SOCK_STREAM, 0);
    if (self.status_client< 0) {
        perror("socket failed");
        return 1;
    }
    printf("[CLIENT] Socket created\n");
    
    // 2. Setup server address
    memset(&server_address, 0, sizeof(server_address));
    server_address->sin_family = AF_INET;
    server_address->sin_port = htons(PORT_CONNECT); // Host TO Network Short (16-bit, for port numbers)
    
    // Convert IP address, check IP address is valid or not
    if (inet_pton(AF_INET,  ip, &server_address->sin_addr) <= 0) {
        perror("Invalid address");
        close(self.status_client);
        return 1;
    }
    
    // 3. connect() - Connect to server
    printf("[CLIENT] Connecting to server...\n");
    if (connect(self.status_client, (struct sockaddr*) &server_address, sizeof(server_address)) < 0) {
        perror("connect failed");
        close(self.status_client);
        return 1;
    }
    printf("[CLIENT] Connected to server\n");

    
    
    // 4. write() - Send data to server
    const char *message = "Hello I'm client!";
    write(self.status_client, message, strlen(message));
    printf("[CLIENT] Sent: %s\n", message);
    
    // 5. read() - Receive response from server
    memset(buffer, 0, BUFFER_SIZE);
    int bytes_read = read(self.status_client, buffer, BUFFER_SIZE);
    if (bytes_read > 0) {
        printf("[CLIENT] Received: %s\n", buffer);
    }
    
    // // 6. close() - Close connection
    close(self.status_client);

    // printf("[CLIENT] Connection closed\n");
    return 0;
}

void Tcp_stream_disconnect()
{

    if (self.status_client >= 0)
        shutdown(self.status_client, SHUT_RDWR);

    if (self.status_serve >= 0)
        shutdown(self.status_serve, SHUT_RDWR);
}

void Tcp_stream_server()
{
    if(Serve_creat(htons(self.address.sin_port)) == 1)
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


void List_all_connect()
{
    printf("--------List all --------\n");
    for(int i =0 ; i< number_connection ; i++)
    {
       printf("%d    %s   %d\n",i,inet_ntoa(connect_socket[i].address.sin_addr),htons(connect_socket[i].address.sin_port));
    }
    printf("-----------------------\n");
}


// int malloc_socket() {
//     connect_socket = malloc(sizeof(info_socket_self) * MAX_CLIENT);
//     if (connect_socket == NULL) return 1;
//     return 0;
// }


// static int control_client()
// {
//     if(number_connection  >= MAX_CLIENT)
//     {
//         return 1;
//     }
//     return 0;
// }

// int Tcp_init()
// {
//     if(malloc_socket() != 0 ) return 1;
//     if (!connect_socket) return 1;
//     number_connection = 0;
//     return 0;
// }

// int check( int exp , const char *msg)
// {
//     if(exp == SOCKETERROR)
//     {
//         perror(msg);
//         exit(1);
//     }
//     return exp;
// }


// int setup_sever()
// {   
//     // int client_socket, address_size;

//     check((self.status_serve = socket(AF_INET, SOCK_STREAM, 0)),"Socket fail\n");

//     self.address.sin_family = AF_INET;
//     self.address.sin_addr.s_addr = INADDR_ANY;
//     // self.address.sin_port = self.Po ;

//     check(bind(self.status_serve,(struct sockaddr*) &self.address,sizeof(struct sockaddr)),"bind fail\n");
//     check(listen(self.status_serve,DEVICE), "fail listen\n ");

//     return self.status_serve;
    

// }

// int accept_new_connection(int sever_socket)
// {
//     int address_size = sizeof(struct sockaddr);

//     info_socket_client *client_socket;

//     client_socket =(info_socket_client * ) malloc(sizeof(info_socket_client));\

//     if (client_socket == NULL)
//     {
//         perror("fail malloc");
//         exit(EXIT_FAILURE);
//     }
//     // int client_socket;
//     // struct sockaddr_in client_addr;

//     check(client_socket->status_client = accept(sever_socket,(struct sockaddr*)&client_socket->address,&address_size),"accept Fail\n");

//     printf("new client accept\n");


//     connect_socket[number_connection] = *client_socket;
//     number_connection ++;
//     //strcpy(connect_socket[number_connection].IP_address,inet_ntoa(client_addr.sin_addr));
//     //connect_socket[number_connection].Port = ntohs(client_addr.sin_port);

//     return client_socket->status_client;

// }

// void Tcp_stream_socket()
// {
//     int sever_socket = setup_sever();

//     fd_set current_set, ready_set;

//     //set all zero
//    FD_ZERO(&current_set);
//     FD_SET(self.status_serve, &current_set);

//     int max_fd = self.status_serve;

//     while (1)
//     {
//         printf("wait for connection\n");

//         ready_set = current_set;

//         int ret = select(max_fd + 1, &ready_set, NULL, NULL, NULL);
//         if (ret < 0)
//         {
//             perror("select failed");
//             exit(EXIT_FAILURE);
//         }

//         for (int fd = 0; fd <= max_fd; fd++)
//         {
//             if (FD_ISSET(fd, &ready_set))
//             {
//                 if (fd == self.status_serve)
//                 {
//                     int client_socket = accept_new_connection(self.status_serve);
//                     if (client_socket > 0)
//                     {
//                         FD_SET(client_socket, &current_set);
//                         if (client_socket > max_fd)
//                             max_fd = client_socket;

//                         printf("New client connected: fd=%d\n", client_socket);
//                     }
//                 }
//                 else
//                 {
//                     char buffer[1024];
//                     int len = recv(fd, buffer, sizeof(buffer) - 1, 0);

//                     if (len <= 0)
//                     {
//                         printf("Client disconnected: fd=%d\n", fd);
//                         close(fd);
//                         FD_CLR(fd, &current_set);
//                     }
//                     else
//                     {
//                         buffer[len] = '\0';
//                         printf("Client[%d]: %s\n", fd, buffer);
//                     }
//                 }
//             }
//         }
//     }


//     if( self.status_client >= 0) shutdown(self.status_client,SHUT_RDWR);
//     if( self.status_serve >= 0) shutdown(self.status_serve,SHUT_RDWR);

// }

// int Client_creat(uint16_t PORT_CONNECT , char *ip)
// {
//     // int self.status_client;
//     struct sockaddr_in server_addr;
//     char buffer[BUFFER_SIZE];
    
//     // 1. socket() - Create socket
//     self.status_client= socket(AF_INET, SOCK_STREAM, 0);
//     if (self.status_client< 0) {
//         perror("socket failed");
//         return 1;
//     }
//     printf("[CLIENT] Socket created\n");
    
//     // 2. Setup server address
//     memset(&server_addr, 0, sizeof(server_addr));
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_port = htons(PORT_CONNECT); // Host TO Network Short (16-bit, for port numbers)
    
//     // Convert IP address, check IP address is valid or not
//     if (inet_pton(AF_INET,  ip, &server_addr.sin_addr) <= 0) {
//         perror("Invalid address");
//         close(self.status_client);
//         return 1;
//     }
    
//     // 3. connect() - Connect to server
//     printf("[CLIENT] Connecting to server...\n");
//     if (connect(self.status_client, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
//         perror("connect failed");
//         close(self.status_client);
//         return 1;
//     }
//     printf("[CLIENT] Connected to server\n");
    
//     // 4. write() - Send data to server
//     const char *message = "Hello I'm client!";
//     write(self.status_client, message, strlen(message));
//     printf("[CLIENT] Sent: %s\n", message);
    
//     // 5. read() - Receive response from server
//     memset(buffer, 0, BUFFER_SIZE);
//     int bytes_read = read(self.status_client, buffer, BUFFER_SIZE);
//     if (bytes_read > 0) {
//         printf("[CLIENT] Received: %s\n", buffer);
//     }
    
//     // // 6. close() - Close connection
//    // close(self.status_client);

//     // printf("[CLIENT] Connection closed\n");
//     return 0;
// }


// void Tcp_stream_client(char *ip , uint16_t PORT)
// {
//     if(Client_creat(PORT,ip) == 1)
//     {
//         fprintf(stderr,"connet fail!!\n");
//         return ;

//     }
// }

// void Tcp_stream_disconnect()
// {

//     // if (g_client_fd >= 0)
//     //     shutdown(g_client_fd, SHUT_RDWR);

//     // if (self.status_serve >= 0)
//     //     shutdown(self.status_serve, SHUT_RDWR);

 

//     for(int i=0;i<number_connection;i++)
//     {
//         if( connect_socket[i].status_client >= 0) shutdown(connect_socket[i].status_client ,SHUT_RDWR);
//         //connect_socket[i].address = NULL;
//         //free(&connect_socket[i]);

//     }    
// }


