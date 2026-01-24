#ifndef BASIC_INFORMATION_H
#define BASIC_INFORMATION_H
#include <string.h>
#include <stdlib.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "communicate.h"
/*Marco*/
#define IP_BUFFER_SIZE 16   
/*fuction creat*/
char *get_local_ip(void);

void fuction_display_help();
void fuction_display_ip();
void fuction_display_port();
void fuction_exit();
#endif