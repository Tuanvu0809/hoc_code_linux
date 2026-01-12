#include <stdio.h>
#include "../include/getcomand.h"
#include <sys/wait.h>
#include <signal.h>

// extern int g_client_fd = -1;

extern info_socket_self self;

int get_command_argument(int argc, char *argv[], char *buffer, int buffer_size) {
    
    if (argc < 2) {
        printf("Enter string !\n");
        return 0;
    }

    if(argc>2)
    {
        printf("Invalid paramater\n");
        return 0;
    }
   
    buffer[0] = '\0'; 

    for (int i = 1; i < argc; i++) {
        if (strlen(buffer) + strlen(argv[i]) + 2 >= buffer_size) {
            printf("long string \n");
            return 0;
        }

        strcat(buffer, argv[i]);
        if (i < argc - 1) {
            strcat(buffer, " "); 
        }
    }

    return 1;
}

int is_number(const char *str)
{
    if (*str == '\0') return 0; 

    while (*str)
    {
        if (!isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}

static command_t Get_Command_ID(const char *cmd)
{
    if (strcmp(cmd, "help") == 0)
        return CMD_HELP;
    if (strcmp(cmd, "exit") == 0)
        return CMD_EXIT;
    if (strcmp(cmd, "myip") == 0)
        return CMD_DISPLAY_IP;    
    if(strcmp(cmd,"connect") == 0)
        return CMD_CONNECT;
    if(strcmp(cmd,"list") == 0)
        return CMD_LIST;
    if(strcmp(cmd,"send") == 0)
        return CMD_SEND;
    if(strcmp(cmd,"myport") == 0)
        return CMD_PORT;
   
    return CMD_UNKNOWN;
}

static int Split_String(char *input, char output[][50], int max_token)
{
    int count = 0;
    char *token = (char *) malloc(sizeof(char)*MAX_PARAMETER);

    if (input == NULL)
        return 0;

    token = strtok(input, " ");
    while (token != NULL && count < max_token)
    {
        strcpy(output[count], token);
        count++;
        token = strtok(NULL, " ");
    }

    free(token);
    return count;  
}
char *getcommand()
{ 
    char *buffer = (char *) malloc(sizeof(char) * BUFFER_SIZE );
    fflush(stdout);

    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    return buffer;
}

static void connect_tcp(char *ip , char *Port_string)
{
    
    if(is_number(Port_string) == 0)
    {
        fprintf(stderr,"Format wrong!!\n");
        return ;
    }
    uint16_t Port_connect = atoi(Port_string);

   Tcp_stream_client(ip,Port_connect);
}
static void send_message(char *index_string, char *message)
{

      if(is_number(index_string) == 0)
    {
        fprintf(stderr,"Format wrong!!\n");
        return ;
    }
    int index = atoi(index_string);
    // char *message;
    // message = getcommand();

   // Tcp_stream_client(ip,Port_connect);
   //Tcp_send_message(index,message);

}

void Exit_fuction()
{
    // pid_t pid;
    // pid = getpid();
    printf("======================================= \n");
    printf("Exit program \n");
    printf("======================================= \n");
   // Tcp_stream_disconnect();
   // kill(pid,SIGUSR1);
  //  exit(0);
}

void Check_Command(uint16_t Port , char *buffer, command_t *choice )
{
    char cmd[MAX_PARAMETER][MAX_SIZE];
    //char *buffer = (char *) malloc(sizeof(char) * BUFFER_SIZE );
    command_t cmd_id;
   
    //buffer = getcommand();
  
    int n = Split_String(buffer,cmd,MAX_PARAMETER);
    cmd_id = Get_Command_ID(cmd[0]);

    *choice = cmd_id;
 
   
    switch (cmd_id)
    {
        case CMD_HELP:
            Help_display_fuction();
            break;
        case CMD_EXIT:
            Tcp_stream_disconnect();
            Exit_fuction();
            break;
        case CMD_DISPLAY_IP:
            Display_ip_fuction();
            break;
        case CMD_CONNECT:
            connect_tcp(cmd[1],cmd[2]);  
            break;
        case CMD_LIST:
            List_all_connect();
            break;
        case CMD_PORT:
            Display_port_fuction();
            break;
        case CMD_SEND:
            send_message(cmd[1],cmd[2]);
            break;
        default:
            printf("Unknown command: %s\n", buffer);
            break;
    }

    free(buffer);

}

