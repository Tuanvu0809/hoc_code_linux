#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

int get_command_argument(int argc, char *argv[], char *buffer, int buffer_size);


int main(int argc, char *argv[])
 {
    printf("Exercise 2||\n");
    char string[50];
    
    if(get_command_argument(argc,argv, string,sizeof(string)) == 0)
    {
        return -1;
    }

    pid_t pid = fork();

    setenv("MY_COMMAND",argv[1],1);

    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        /* ===== Child process ===== */
        char *cmd = getenv("MY_COMMAND");

        if (cmd == NULL)
        {
            printf("MY_COMMAND not set\n");
            exit(1);
        }
         execvp(cmd, &argv[1]);
        perror("execlp failed");
        exit(1);
    }
    else
    {
        /* ===== Parent process ===== */
        wait(NULL);
        printf("Parent: child finished\n");
    }

    return 0;
}



int get_command_argument(int argc, char *argv[], char *buffer, int buffer_size) {
    
    if (argc == 1) {
        printf("Enter string !\n");
        return 0;
    }

    buffer[0] = '\0'; 

    for (int i = 0; i < argc; i++) {
        if (strlen(buffer) + strlen(argv[i]) + 2 >= buffer_size) {
            printf("long string \n");
            return 0;
        }

        strcat(buffer, argv[i]);
        if (i < argc - 1) {
            strcat(buffer, " "); 
        }
    }

    return -1;
}