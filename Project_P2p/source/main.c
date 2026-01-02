#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "../include/getcomand.h"
#include "../include/basic_infomation.h"

// command_t User_choice = CMD_START;
command_t User_choice = CMD_HELP; 
uint16_t Port; 
//bool Flag_check_blind = false;

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
        fprintf(stderr,"Format wrong!!\n");
        return -1;
    }
    Port = atoi(PORT_cmd);

    signal(SIGUSR1,Tcp_stream_disconnect);    
   
    Help_display_fuction();


    pthread_t Serve, Client;

    pthread_create(&Serve,NULL,Serve_mission, &Port);
    pthread_create(&Client,NULL,Client_mission,&Port);

    pthread_join(Serve,NULL);
    pthread_join(Client,NULL);

    // void Tcp_stream_disconnect();

    return 0;
}

void *Client_mission(void *index)
{

    uint16_t Port = *(uint16_t *) index;
    
   sleep(1);
    signal(SIGUSR1,Tcp_stream_disconnect);
    
    while(User_choice != CMD_EXIT)
    {
        printf("Enter the command: ");
        char *command;
        command = getcommand();
        Check_Command(Port,command,&User_choice);
       
    }
    //Tcp_stream_disconnect();
    
    return NULL;
}

void *Serve_mission(void *index)
{
//     int server_fd , client_fd;
    while(User_choice != CMD_EXIT)
    {
   
            Tcp_stream_server(Port);
        
        // close(client_fd);
        // close(server_fd);
    }

    printf("Thread serve end\n ");
    return NULL;
}


