#ifndef BASIC_INFORMATION_H
#define BASIC_INFORMATION_H
#include <string.h>
#include <stdlib.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define IP_BUFFER_SIZE 16   

char *Get_Local_IP(void);

void Help_display_fuction();
void Display_ip_fuction();
void Display_port_fuction();
void Exit_fuction();
#endif