#ifndef COMMUNICATE_H
#define COMMUNICATE_H
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "basic_infomation.h"
#include "getcomand.h"
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/types.h>
#include <poll.h>

#define BUFFER_SIZE 1024
#define DEVICE      5
#define MAX_CLIENT 10
#define SOCKETERROR (-1)
#define MAX_CHARACTER   50
#define INDEX_MESSAGE_STRING_FOR_SEND_MESSAGE   7
#define PORT_FREE 1
#define PORT_BUSY 0
#define PORT_ERROR -1

typedef struct{
    struct sockaddr_in address;
    int status_serve;
    int status_client;

}  information_self_socket;

typedef struct{
    struct sockaddr_in address;
    int status;
    // int status_serve;
    // int status_client;
  
}   information_connect_socket;

int Send_message_to_connect(int index, const char *message);
int malloc_connect_socket();
int is_port_free(uint16_t Port);
int Serve_creat(uint16_t PORT_CONNECT);
int Client_creat(uint16_t PORT_CONNECT , char *ip);

void Tcp_stream_server();
void Tcp_stream_client();
void Tcp_stream_disconnect();
void List_all_connect();


#endif