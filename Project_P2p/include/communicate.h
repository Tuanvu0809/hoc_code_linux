#ifndef COMMUNICATE_H
#define COMMUNICATE_H
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "basic_infomation.h"
#include "getcomand.h"

#define BUFFER_SIZE 100
#define DEVICE      5
#define MAX_CLIENT 10
#define SOCKETERROR (-1)
// extern int g_client_fd;

// typedef struct{
//     uint16_t Port;
//     struct sockaddr_in server_socket;
// } Serve_connect;

typedef struct{
    struct sockaddr_in address;
    int status_serve;
    int status_client;

}  info_socket_self;

typedef struct{
    struct sockaddr_in address;
    int status_client;
  
}   info_socket_client;

// int tcp_connect(const char *ip, uint16_t Port_serve);
// void Tcp_connect_fuction(const char *ip, const char *Port_serve);
// int Tcp_init();
void Tcp_stream_server();
void Tcp_stream_client(char *ip , uint16_t PORT);

void Tcp_stream_disconnect();
// int Serve_creat();

void List_all_connect();

// int malloc_socket();
// void recv_client_data(int index);
// void accept_new_client(void);

#endif