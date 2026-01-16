#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

int main()
{
    printf("zombie process:\n");

    pid_t pid = fork();

    if(pid == 0)
    {
        printf("==child process== \n");
        printf("Parent PID: %d\n",getppid());
        printf("PID %d\n",getpid());
        printf("Value of PID: %d\n",pid);
        sleep(5);
    
        exit(10);
    }
    else {
        printf("==Parent process== \n");
        printf("\n====Parent====\n");
        printf("Parent PID: %d\n",getpid());
        printf("Value of PID: %d\n",pid);
        //sleep(5);
        printf("==parent finish==\n");
    }
    return 0;
}