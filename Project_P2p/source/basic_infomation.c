#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../include/basic_infomation.h"
#include "../include/communicate.h"
char ip_address[IP_BUFFER_SIZE];
extern info_socket_self self;

char *Get_Local_IP(void)
{
    struct ifaddrs *ifaddr, *ifa;

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        return NULL;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == NULL)
            continue;

        /* Check IPv4 */
        if (ifa->ifa_addr->sa_family == AF_INET)
        {
            struct sockaddr_in *sa = (struct sockaddr_in *)ifa->ifa_addr;
            const char *addr = inet_ntoa(sa->sin_addr);

            /* Skip localhost */
            if (strcmp(addr, "127.0.0.1") != 0)
            {
                strncpy(ip_address, addr, IP_BUFFER_SIZE);
                break;
            }
        }
    }

    freeifaddrs(ifaddr);
    return ip_address;
} 

void Help_display_fuction()
{
    printf("=========Help display============== \n");
    printf("Use the command below\n");
    printf("1.help                               :  display user interface option\n");
    printf("2.myip                               : display IP address\n");
    printf("3.myport                             :display listening port of this app\n");
    printf("4.connect <destination> <port no>    : connect to another computer\n");
    printf("5.list                               : list all connections of this app\n");
    printf("6.terminate <connection ip>          : terminal connection\n");
    printf("7.send <connect id> <message>        : send the message to a connection\n");
    printf("8.exit                               :  close all connection all terminate app\n");
    printf("======================================= \n");
}
void Display_ip_fuction()
{
//     printf("========= IP address display============== \n");
 
//     if (ip_address)
//         printf("Local IP: %s\n", inet_ntoa(self.address.sin_addr));
//     else
//         printf("Cannot get IP\n");
//     printf("======================================= \n");

   char ip_str[INET_ADDRSTRLEN];

    printf("========= IP address display ==============\n");

    if (self.address.sin_addr.s_addr != 0)
    {
        if (inet_ntop(AF_INET,
                      &self.address.sin_addr,
                      ip_str,
                      sizeof(ip_str)) != NULL)
        {
            printf("Local IP: %s\n", ip_str);
        }
        else
        {
            perror("inet_ntop failed");
        }
    }
    else
    {
        printf("IP address not set\n");
    }

    printf("===========================================\n");
 }

void Display_port_fuction()
{
    printf("=========Port display============== \n");
  
    if (ip_address)
        printf("PORT : %d\n", htons(self.address.sin_port));
    else
        printf("Cannot get PORT \n");
    printf("======================================= \n");
}

