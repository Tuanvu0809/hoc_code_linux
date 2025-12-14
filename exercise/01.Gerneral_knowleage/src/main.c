#include <stdio.h>
#include "../inc/strutils.h"
#include <string.h>
/*Fuction creat*/
int get_command_argument(int argc, char *argv[], char *buffer, int buffer_size);

int main(int argc, char *argv[])
{
    char string[50];
    int number = 0;
    printf("Exercise 1 | Static and Shared Library \n");

    if(!get_command_argument(argc,argv, string,sizeof(string)))
    {
        printf("fail \n");
        return -1;
    }

    printf("source string: \t %s\n",string);

    str_reverse(string);
    str_trim(string);

    if(str_to_int(string, &number) != -1)
    { 

       printf("string convrt interger and add 1: %d \n", number + 1);
    }
   
    return 0;
}

int get_command_argument(int argc, char *argv[], char *buffer, int buffer_size) {
    
    if (argc < 2) {
        printf("Enter string !\n");
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