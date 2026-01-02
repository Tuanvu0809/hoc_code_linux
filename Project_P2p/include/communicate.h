#ifndef COMMUNICATE_H
#define COMMUNICATE_H
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "basic_infomation.h"
#include "getcomand.h"

#define BUFFER_SIZE 100
#define DEVICE      5
// extern int g_client_fd;

// typedef struct{
//     uint16_t Port;
//     struct sockaddr_in server_socket;
// } Serve_connect;

// int tcp_connect(const char *ip, uint16_t Port_serve);
// void Tcp_connect_fuction(const char *ip, const char *Port_serve);
void Tcp_stream_server(uint16_t PORT);
void Tcp_stream_client( char *ip, uint16_t PORT);
void Tcp_stream_disconnect();
// void List_all_connect();
#endif