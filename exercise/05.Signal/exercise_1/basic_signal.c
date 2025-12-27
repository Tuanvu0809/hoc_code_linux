#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
int count = 0;
void Handle_signal(int sig)
{
    
    printf("\nSIGINT received : %d and count %d \n", sig,count);
    count ++;
    if (count >= 3) 
    {
        exit(0);
    }
}

int main(){

    printf("===EX1 || Demo Signal===\n");
    signal( SIGINT,Handle_signal);

    while(1)
    {
        printf("main still running\n");
        sleep(1);
    }
    return 0;
}