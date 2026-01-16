#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>
#include "../include/getcomand.h"
#include "../include/basic_infomation.h"

// command_t User_choice = CMD_START;
command_t User_choice = CMD_HELP; 
uint16_t Port; 

info_socket_self self;
info_socket_connect *connect_socket;

int number_connection  = 0 ;

void *Client_mission(void *index);
void *Serve_mission(void *index);

int main(int argc, char *argv[])
{
    printf("APP P2P\n");
    char PORT_cmd[100];
    if(get_command_argument(argc,argv,PORT_cmd,BUFFER_SIZE) == 0)
    {
        fprintf(stderr,"Format wrong!!\n");
        return -1;

    }
    if(is_number(PORT_cmd) == 0)
    {
        fprintf(stderr,"Format wrong!! \n");
        return -1;
    }

    if(malloc_socket() != 0)
    {
        printf("socket error\n");
        return -1;
    }

    self.address.sin_addr.s_addr = inet_addr(Get_Local_IP());
    self.address.sin_port = htons(atoi(PORT_cmd));


    self.status_serve = -1 ; 

    printf(" self socket %s %d %s %s",inet_ntoa(self.address.sin_addr),htons(self.address.sin_port),self.status_client != -1 ? "yes": "no",self.status_serve != -1 ? "yes": "no");
    printf("\n sizeof socket %ld\n",sizeof(self));

    fflush(stdin);
  
    Help_display_fuction();

    pthread_t Serve, Client;

    pthread_create(&Serve,NULL,Serve_mission, &Port);
    pthread_create(&Client,NULL,Client_mission,&Port);

    pthread_join(Serve,NULL);
    pthread_join(Client,NULL);

    return 0;
}
void *Client_mission(void *index)
{

    uint16_t Port = *(uint16_t *) index;
    
   
    
    while(User_choice != CMD_EXIT)
    {
        sleep(1);
        printf("Enter the command: ");
        char *command;
        command = getcommand();
        Check_Command(Port,command,&User_choice);
       
    }

    
    return NULL;
}

void *Serve_mission(void *index)
{

    while(User_choice != CMD_EXIT)
    {
        Tcp_stream_server();

    }

    printf("Thread serve end\n ");
    return NULL;
}