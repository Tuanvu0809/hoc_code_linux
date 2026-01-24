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
/*Variable global*/
command_t  choice_user = CMD_HELP; 
uint16_t Port; 
information_self_socket self;
information_connect_socket *connect_socket;
int number_of_connection  = 0 ;

/*Fuction*/
void *task_client(void *index);
void *task_server(void *index);
int check_condition_port_is_correct(char *Port_cmd);

int main(int argc, char *argv[])
{
    printf("APP P2P\n");
    char PORT_cmd[100];
    /*Check argument*/
    if(get_parameter_initial(argc,argv,PORT_cmd,BUFFER_SIZE) != SUCCESS)
    {
        fprintf(stderr,"Format wrong!!\n");
        return FAIL;

    }
    /* Check port */
    if(check_condition_port_is_correct(PORT_cmd) != 0)
    {
        fprintf(stderr,"PORT wrong!! \n");
        return FAIL;
    }
    /**/
    if(malloc_connect_socket() != 0)
    {
        fprintf(stderr,"socket error\n");
        return FAIL;
    }

    self.address.sin_addr.s_addr = inet_addr(get_local_ip());
    self.address.sin_port = htons(Port);
    self.status_serve = -1 ; 

    printf(" self socket %s %d",inet_ntoa(self.address.sin_addr),htons(self.address.sin_port));
    printf("\n sizeof socket %ld\n",sizeof(self));

    fflush(stdin);
  
    fuction_display_help();

    pthread_t serve, client;

    pthread_create(&serve,NULL,task_server, &Port);
    pthread_create(&client,NULL,task_client,&Port);

    while( choice_user != CMD_EXIT)
    {
        sleep(1);
        printf("\nEnter the command: ");
        fflush(stdin);
        char *command;
        command = getcommand();
        Check_Command(Port,command,& choice_user);
       
    }
  

    pthread_join(serve,NULL);
    pthread_join(client,NULL);

    return SUCCESS;
}
void *task_client(void *index)
{

    socklen_t len = sizeof(self.address);
    
   
    while( choice_user != CMD_EXIT)
    {
    
        Tcp_stream_client();
       
    }

    
    return NULL;
}

void *task_server(void *index)
{
    
    if(is_port_free(self.address.sin_port) != PORT_FREE )
    {
        fprintf(stderr,"Port problem");
        close(self.status_serve);
         choice_user = CMD_EXIT;
        return NULL ;
    }
    if(Serve_creat(htons(self.address.sin_port)) == 1)
    {
        fprintf(stderr,"connet fail!!\n");
        close(self.status_serve);
        choice_user = CMD_EXIT;
        return  NULL;

    }

    while( choice_user != CMD_EXIT)
    {
        Tcp_stream_server();

    }

    printf("Thread serve end\n ");
    return NULL;
}

int check_condition_port_is_correct(char *PORT_cmd)
{
   
    if(is_number(PORT_cmd) != SUCCESS)
    {
        fprintf(stderr,"Format wrong!! \n");
        return FAIL;
    }

    Port = atoi(PORT_cmd);

    if(Check_Port_Permission(Port) != 0)
    {
        fprintf(stderr,"Port can't access\n");
        return FAIL;
    }

    return SUCCESS;
}