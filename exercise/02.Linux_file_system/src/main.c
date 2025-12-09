#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../inc/filestat.h"
#include <stdlib.h>

int get_command_argument(int argc, char *argv[], char *buffer, int buffer_size);

int main(int argc, char *argv[])
{
    char string[100];
    printf("Exercise 2 || \n ");

    if(!get_command_argument(argc,argv, string,sizeof(string)))
    {
        printf("Run the promgram with path \n example: .\\filestat deskop\n");
        return 1;
    }

    struct stat file;

    if (stat(argv[1], &file) == -1)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    
    }
    file_path(argv[0]);
    file_type(&file);
    file_bytes(&file);
    file_times(&file);

    return 0;
}

int get_command_argument(int argc, char *argv[], char *buffer, int buffer_size) {
    
    if (argc != 2) {
       
        return 0;
    }

    buffer[0] = '\0'; 

    strncpy(buffer, argv[1], buffer_size - 1);
    buffer[buffer_size - 1] = '\0';

    return 1;
}