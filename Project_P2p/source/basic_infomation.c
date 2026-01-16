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
    printf("========= IP address display============== \n");
 

    printf("Local IP: %s\n", Get_Local_IP());

    printf("======================================= \n");

}

void Display_port_fuction()
{
    printf("=========Port display============== \n");
  
    if (htons(self.address.sin_port))
        printf("PORT : %d\n", htons(self.address.sin_port));
    else
        printf("Cannot get PORT \n");
    printf("======================================= \n");
}

