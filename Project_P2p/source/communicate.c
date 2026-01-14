#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/types.h>
#include "../include/communicate.h"

extern info_socket_self self;
extern info_socket_connect *connect_socket;

extern command_t User_choice ; 

// extern int number_connection;
int number_connection  = 0 ;

int Serve_creat(uint16_t PORT_CONNECT)
{
    printf("Serve Stream \n") ; 
    //  int server_fd ; 

    // struct sockaddr_in *client_address;
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
    while(1){
        connect_other->status = accept(self.status_serve,(struct sockaddr*) &connect_other->address,&connect_size);

        if (connect_other->status < 0) 
        {
            perror("accept failed");
            close(self.status_serve);
            return 1;
        }
        printf("Listening...\n");


        printf("[SERVER] Client connected from %s:%d\n", inet_ntoa(connect_other->address.sin_addr), ntohs(connect_other->address.sin_port));

        /*save connect */
       
        connect_socket = connect_other;
        number_connection ++;

        // 5. read() - Receive data from client
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_read = read(connect_other->status, buffer, BUFFER_SIZE);
        if (bytes_read > 0) {
            printf("[SERVER] Received: %s\n", buffer);
        }
        
        // 6. write() - Send response to client
        const char *response = "Hello I'm server!";
        write(connect_other->status, response, strlen(response));
        printf("[SERVER] Sent: %s\n", response);
        
        // 7. close() - Close connections
        //close(connect_other->status);
       // close(self.status_serve);
    }


    printf("[SERVER] Connection closed\n");
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

    
    // connect_socket[number_connection].address = *server_address;
    // connect_socket[number_connection].status = self.status_client;
    // number_connection ++;
    connect_other->status = self.status_client;
    connect_socket = connect_other;
    number_connection ++;
    // 4. write() - Send data
    const char *message = "Hello I'm client!";
    if (write(self.status_client, message, strlen(message)) < 0) {
        perror("write failed");
    }

    // 5. read() - Receive data
    int bytes_read = read(self.status_client, buffer, BUFFER_SIZE - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("[CLIENT] Received: %s\n", buffer);
    }

    // 6. close() - Close connection
    //close(self.status_client);

    return 0;
}


void Tcp_stream_disconnect()
{

    if (self.status_client >= 0)
        shutdown(self.status_client, SHUT_RDWR);

    if (self.status_serve >= 0)
        shutdown(self.status_serve, SHUT_RDWR);
    for(int i=0; i< number_connection; i++)
    {
        if(connect_socket[i].status >= 0)
        {
            shutdown(connect_socket[i].status,SHUT_RDWR);
            free(&connect_socket[i]);
        }
    }
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
    char self_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &self.address.sin_addr,  self_ip, sizeof(self_ip));

    // if (ip != NULL &&  strcmp(ip, self_ip) == 0 && PORT == ntohs(self.address.sin_port))
    // {
    //     printf("self connect\n");
    //     return;
    // }
    
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
       printf("%d    %s   %d %s \n",i,inet_ntoa(connect_socket[i].address.sin_addr),htons(connect_socket[i].address.sin_port),connect_socket[i].status > 0 ? "connect":"disconnect" );
    
    }
    printf("-----------------------\n");
}


int malloc_socket() {
    connect_socket = malloc(sizeof(info_socket_self) * MAX_CLIENT);
    if (connect_socket == NULL) return 1;
    return 0;
}
