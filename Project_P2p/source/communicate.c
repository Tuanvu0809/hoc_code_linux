#include <stdio.h>
#include <fcntl.h>
#include "../include/communicate.h"

extern information_self_socket self;
extern information_connect_socket *connect_socket;
extern command_t  choice_user ; 
extern int number_of_connection ;


int is_port_free(uint16_t Port)
{
    int sockfd;
    struct sockaddr_in addr;
    int opt = 1;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return PORT_ERROR;
    }

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(Port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        close(sockfd);

        if (errno == EADDRINUSE)
            return PORT_BUSY;   
        else
            return PORT_ERROR;  
    }

    close(sockfd);
    return PORT_FREE;
}


void poll_read_clients_serve(int server_fd, information_connect_socket *clients, int *number_client)
{
    struct pollfd fds[MAX_CLIENT + 1];
    char buffer[BUFFER_SIZE];

    int nfds = 0;

    /* 1️⃣ server socket */
    fds[nfds].fd = server_fd;
    fds[nfds].events = POLLIN;
    nfds++;

    /* 2️⃣ client sockets */
    for (int i = 0; i < *number_client; i++) {
        fds[nfds].fd = clients[i].status;
        fds[nfds].events = POLLIN;
        nfds++;
    }

    int ready = poll(fds, nfds, -1);
    if (ready < 0) {
        perror("poll");
        return;
    }

      /* 4️⃣ đọc dữ liệu client */
    for (int i = 1; i < nfds; i++) {

        if (fds[i].revents & POLLIN) {

            int idx = i - 1; // vì fds[0] là server
            int fd = clients[idx].status;
            int n = read(fd, buffer, BUFFER_SIZE - 1);

            if (n > 0) {
                buffer[n] = '\0';

                printf("\n******************************\n");
                printf(" Message receive from client %s\n" , inet_ntoa(clients[idx].address.sin_addr) );
                printf("From Port %d\n",htons(clients[idx].address.sin_port));
                printf("Message: %s\n", buffer);
                printf("\n******************************\n");
            }
    
        }
    }

    /* 3️⃣ accept client mới */
    if (fds[0].revents & POLLIN) {
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);

        int client_fd = accept(server_fd, (struct sockaddr *)&addr, &len);
        
        if (client_fd >= 0 && *number_client < MAX_CLIENT)
        {
            clients[*number_client].status = client_fd;
            clients[*number_client].address = addr;
            (*number_client)++;

            printf("\nNew client:ip=%s port=%d\n",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));
        }
    }

  
}

void poll_read_client(information_connect_socket *clients, int *number_client)
{
    struct pollfd fds[MAX_CLIENT];
    char buffer[BUFFER_SIZE];

    int nfds = 0;

    /* 1️⃣ add all connected sockets */
    for (int i = 0; i < *number_client; i++) {
        if (clients[i].status >= 3) {
            fds[nfds].fd = clients[i].status;
            fds[nfds].events = POLLIN;
            nfds++;
        }
    }

    if (nfds == 0) {
        return;
    }

    int ready = poll(fds, nfds, -1); 
    if (ready < 0) {
        perror("poll");
        return;
    }
    
    for (int i = 0; i < nfds; i++) {

        if (fds[i].revents & POLLIN) {

            int fd = fds[i].fd;
            int n = read(fd, buffer, BUFFER_SIZE - 1);

            if (n > 0) {
                buffer[n] = '\0';

                printf("\n******************************\n");
                printf("Message receive from serve %s\n" , inet_ntoa(clients[i].address.sin_addr) );
                printf("From Port %d\n",htons(clients[i].address.sin_port));
                printf("Message: %s\n", buffer);
                printf("******************************\n");
            }
          
        }
    }
}



int Serve_creat(uint16_t PORT_CONNECT)
{
    printf("Serve Stream \n") ; 

    socklen_t connect_size = sizeof(struct sockaddr_in); 
    information_connect_socket *connect_other;
    
    char buffer[BUFFER_SIZE];
    connect_other = (information_connect_socket *)malloc(sizeof(information_connect_socket));

    connect_other->status = -1;

    if (!connect_other) {
        perror("malloc failed");
         return FAIL;;
    }
    /*Serve */
    //Creat socket
    self.status_serve = socket(AF_INET,SOCK_STREAM,0);
    if( self.status_serve < 0)
    {
        perror("fail creat serve socket \n");
        return 1;
    }
    
   // fcntl(self.status, F_SETFL, O_NONBLOCK);
    
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

    printf("[SERVER] Bound to Port %d\n", PORT_CONNECT);
    //listen 
    if( listen(self.status_serve,DEVICE) < 0)
    {
        perror("fail listen\n");
        close(self.status_serve);
        return 1;
    }

    printf("wait client...\n");
    // while(1)
    // {
        // connect_other->status = accept(self.status,(struct sockaddr*) &connect_other->address,&connect_size);

        // if (connect_other->status < 0) 
        // {
        //     perror("accept failed");
        //     close(self.status);
        //     return 1;
        // }
        // printf("\nListening...\n");
        // /*save connect */
      
        // connect_socket[number_of_connection] = *connect_other;
        // number_of_connection ++;

        // close(connect_socket[number_of_connection].status);
        // number_of_connection ++;
  
        // 5. read() - Receive data from client
       // memset(buffer, 0, BUFFER_SIZE);
        // int bytes_read = read(connect_other->status, buffer, BUFFER_SIZE);
        // if (bytes_read > 0) {
        //     printf(" Received from : %s\n", buffer);
        // }

        //  poll_read_clients(connect_socket,&number_of_connection);
        
        // // 6. write() - Send response to client
        // const char *response = "Hello I'm server!";
        // write(connect_other->status, response, strlen(response));
        // printf("[SERVER] Sent: %s\n", response);
        
        // 7. close() - Close connections
        //close(connect_other->status);
       
   // }


     return SUCCESS;
}

int Client_creat(uint16_t PORT_CONNECT , char *ip)
{

    information_connect_socket *connect_other;
  
    char buffer[BUFFER_SIZE];

    /* malloc sockaddr_in */
    connect_other = (information_connect_socket *)malloc(sizeof(information_connect_socket));
    if (!connect_other) {
        perror("malloc failed");
         return FAIL;;
    }
      socklen_t len = sizeof(connect_other->address);

    // 1. socket() - Create socket
    self.status_client = socket(AF_INET, SOCK_STREAM, 0);
    if (self.status_client < 0) {
        perror("socket failed");
        free(connect_other);
         return FAIL;;
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
        return FAIL;;
    }

    // 3. connect() - Connect to server
    printf("[CLIENT] Connecting to server...\n");
    if (connect(self.status_client,  (struct sockaddr *) &connect_other->address,  sizeof(struct sockaddr_in)) < 0) {
        perror("connect failed");
        close(self.status_client);
        free(connect_other);
         return FAIL;;
    }
    printf("[CLIENT] Connected to server\n");

   // socklen_t len = sizeof(self.address);

    // connect_other->status = accept(self.status,  (struct sockaddr *)&self.address,  &len);

    // if (connect_other->status < 0) {
    //     perror("accept failed");
    //     return FAIL;
    // }


   // connect_other->status = accept(connect_other->status,(struct sockaddr *) &self.address,&len);
    connect_other->status = self.status_client;
    connect_socket[number_of_connection] = *connect_other;
    
 
    // 4. write() - Send data
    // const char *message = "Hello I'm client!";
    // if (write(self.status_client, message, strlen(message)) < 0) {
    //     perror("write failed");
    // }
 
    // // 5. read() - Receive data
    // int bytes_read = read(self.status_client, buffer, BUFFER_SIZE - 1);
    // if (bytes_read > 0) {
    //     buffer[bytes_read] = '\0';
    //     printf("[CLIENT] Received: %s\n", buffer);
    // }

    // 6. close() - Close connection
    // close(self.status_client);
    // close(connect_socket[number_of_connection].status);

    number_of_connection ++;
  
    free(connect_other);

    return SUCCESS;
}

int Send_message_to_connect(int index, const char *message)
{
    ssize_t sent;
    int fd = connect_socket[index].status;

    if (fd < 3) {
        fprintf(stderr, "invalid socket fd=%d\n", fd);
        return FAIL;
    }

    sent = send(fd, message, strlen(message), 0);
    if (sent < 0) {
        perror("send failed");
        return FAIL;
    }

    return SUCCESS;

}

void Tcp_stream_disconnect()
{

    if (self.status_client >= 0)
        shutdown(self.status_client, SHUT_RDWR);

    if (self.status_serve >= 0)
        shutdown(self.status_serve, SHUT_RDWR);
   
    if (connect_socket != NULL){    
        // shutdown(connect_socket->status_client,SHUT_RDWR);
         shutdown(connect_socket->status,SHUT_RDWR);
        free(connect_socket);
    }    
    
}

void Tcp_stream_server()
{
    poll_read_clients_serve(self.status_serve,connect_socket,&number_of_connection);

}

void Tcp_stream_client()
{
    poll_read_client(connect_socket,&number_of_connection);

}


void List_all_connect()
{
    printf("--------List all --------\n");
    // printf("serve:    %s   %d %d %s \n",inet_ntoa(self.address.sin_addr),htons(self.address.sin_port),self.status_client,connestatus > 0 ? "connect":"disconnect" );

    for(int i =0 ; i< number_of_connection ; i++)
    {
       printf("%d    %s   %d %d \n",i,inet_ntoa(connect_socket[i].address.sin_addr),htons(connect_socket[i].address.sin_port),connect_socket[i].status );
    
    }
    printf("-----------------------\n");
}


int malloc_connect_socket() {
    connect_socket = malloc(sizeof(information_self_socket) * MAX_CLIENT);
    if (connect_socket == NULL) return 1;
     return SUCCESS;
}
