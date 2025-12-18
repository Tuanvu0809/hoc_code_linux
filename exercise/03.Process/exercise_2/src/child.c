#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int get_command_argument(int argc, char *argv[], char *buffer, int buffer_size);

int main(int argc, char *argv[]) {
    
    char *command_recieve = getenv("MY_COMMAND");
    if(!command_recieve)
    {
        perror("fail cmd\n");
        return -1;
    }
    printf("Read the env variable:  %s\n ",  command_recieve);
    if (argc > 1)
    {
        execlp(command_recieve, argv[0],NULL );
    } 
    else 
    {
        char *args[] = { command_recieve, NULL };
        execvp(command_recieve, args);
    }

    
    perror("fail child \n");
    return 0;
}
