#include <stdio.h>
#include "../include/getcomand.h"
#include <sys/wait.h>
#include <signal.h>
#include "../include/basic_infomation.h"

/*variable extern from main*/
extern information_self_socket self;
extern information_connect_socket *connect_socket;
extern int number_of_connection ;

int Check_socket_connect(char *ip , uint16_t Port)
{
    if (ip != NULL && strcmp(ip, get_local_ip()) == 0 && Port== ntohs(self.address.sin_port))
    {
        fprintf(stderr,"self connect\n");
         return FAIL; ;
    }

    for( int index = 0; index< number_of_connection ;index++ )
    {
        if ( strcmp(ip, get_local_ip()) == 0 && Port== ntohs(connect_socket[index].address.sin_port))
        {
            fprintf(stderr,"already connect\n");
            return FAIL; 
        }   
    }

    return SUCCESS;
}

int get_parameter_initial(int argc, char *argv[], char *buffer, int buffer_size) {
    
    if (argc < 2) {
        printf("Enter string !\n");
        return FAIL;
    }

    if(argc > 2)
    {
        printf("Invalid paramater\n");
        return FAIL;
    }
   
    buffer[0] = '\0'; 

    for (int i = 1; i < argc; i++) {
        if (strlen(buffer) + strlen(argv[i]) + 2 >= buffer_size) {
            printf("long string \n");
            return FAIL;
        }

        strcat(buffer, argv[i]);
        if (i < argc - 1) {
            strcat(buffer, " "); 
        }
    }

    return SUCCESS;
}

int is_number(const char *str)
{
    if (*str == '\0') return FAIL; 

    while (*str)
    {
        if (!isdigit(*str))
            return FAIL;
        str++;
    }
    return SUCCESS;
}
int Check_Port_Permission(uint16_t Port)
{
    fprintf(stderr,"Port can accept from %d to %d\n",PORT_MIN,PORT_MAX);
   return (Port > PORT_MIN && Port < PORT_MAX) ? 0 : 1;
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
    if (input == NULL) return SUCCESS;

    char *check_string = malloc(strlen(input) + 1);
    if (!check_string) return SUCCESS;

    strcpy(check_string, input);

    int count = 0;
    char *token = strtok(check_string, " ");

    while (token != NULL && count < max_token)
    {
        strncpy(output[count], token, 49);
        output[count][49] = '\0';  
        count++;
        token = strtok(NULL, " ");
    }

    free(check_string);   
    return count;
}


char *getcommand()
{ 

    char *buffer = (char *) malloc(sizeof(char) * BUFFER_SIZE );
    fflush(stdout);
    fflush(stdin);
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; 

    return buffer;
}

static void connect_tcp(char *ip , char *Port_string)
{
    
    if(is_number(Port_string) != SUCCESS)
    {
        fprintf(stderr,"Format wrong!!\n");
        return ;
    }
    uint16_t Port_connect = atoi(Port_string);
 
    if (Check_socket_connect(ip,Port_connect) != 0  )
    {
        fprintf(stderr,"Can't connect socket\n");
        return;
    }

    socklen_t len = sizeof(self.address);

    
    if(Client_creat(Port_connect,ip) == 1)
    {
        fprintf(stderr,"connet fail!!\n");
        return ;

    }
    printf("\nConnect success, ready to send data \n");
    // Tcp_stream_client(ip,Port_connect);

   
}
static void send_message(char *index_string, char *message)
{

    if(is_number(index_string) != SUCCESS)
    {
        fprintf(stderr,"Format wrong!!\n");
        return ;
    }
    int index = atoi(index_string);
    if(index >= MAX_CLIENT)
    {
        fprintf(stderr,"index out of range");
        return ;
    }
    
    message = message + INDEX_MESSAGE_STRING_FOR_SEND_MESSAGE;
    
    printf("message is : %s \n", message);

    if(Send_message_to_connect(index,message) != SUCCESS)
    {
        fprintf(stderr,"\n send message error\n ");
        return ;
    }

}

void fuction_exit()
{
    Tcp_stream_disconnect();
    printf("======================================= \n");
    printf("Exit program \n");
    printf("======================================= \n");

}


void Check_Command(uint16_t Port , char *buffer, command_t *choice )
{
    char cmd[MAX_PARAMETER][MAX_SIZE];
    command_t cmd_id;

    memset(cmd,0,sizeof(cmd));
    int n = Split_String(buffer,cmd,MAX_PARAMETER);
    
    if(n > MAX_PARAMETER)
    {
        printf(" too much length\n");
        return;
    }

    cmd_id = Get_Command_ID(cmd[0]);
    *choice = cmd_id;
       
    switch (cmd_id)
    {
        case CMD_HELP:
            fuction_display_help();
            break;
        case CMD_EXIT:
            fuction_exit();
            break;
        case CMD_DISPLAY_IP:
            fuction_display_ip();
            break;
        case CMD_CONNECT:
            connect_tcp(cmd[1],cmd[2]);  
            break;
        case CMD_LIST:
            List_all_connect();
            break;
        case CMD_PORT:
            fuction_display_port();
            break;
        case CMD_SEND:
            send_message(cmd[1],buffer);
            break;
        default:
            printf("Unknown command: %s\n", buffer);
            break;
    }

   // free(buffer);

}