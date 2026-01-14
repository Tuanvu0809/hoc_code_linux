#ifndef GET_COMMAND_H
#define GET_COMMAND_H
#include <string.h>
#include <ctype.h>
#include "basic_infomation.h"
#include "communicate.h"
#include <stdlib.h>

#define BUFFER_SIZE 100
#define MAX_PARAMETER   10
#define MAX_SIZE     50

typedef enum{
    CMD_START = 0,
    CMD_HELP ,
    CMD_EXIT,
    CMD_DISPLAY_IP,
    CMD_PORT,
    CMD_CONNECT,
    CMD_LIST,
    CMD_SEND,
    CMD_READ,
    CMD_UNKNOWN,

}command_t; 

int get_command_argument(int argc, char *argv[], char *buffer, int buffer_size) ;
void Check_Command(uint16_t Port , char *buffer, command_t *choice );
int is_number(const char *str);
char *getcommand();

#endif