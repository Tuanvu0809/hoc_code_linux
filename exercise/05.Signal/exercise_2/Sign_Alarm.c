#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

volatile sig_atomic_t time_count = 0;
void Sigalrm_handler(int sig)
{
    time_count ++;
 
    printf(" Handler Alarm - %d second\n",time_count);

    if(time_count >= 10)
    {
        exit(0);
    }
    alarm(1);
}
int main()
{
    printf("Exercise 2|| Sigalrm\n");
    signal(SIGALRM,Sigalrm_handler);
    alarm(1);
    while(1);
  
    return 0;
}