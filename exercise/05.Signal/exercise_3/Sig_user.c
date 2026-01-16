#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <wait.h>

volatile sig_atomic_t send_count = 0;

void Siguser_handler(int sig)
{
    send_count ++;
    char message[] = "Received signal from parent\n";
  
    write(STDOUT_FILENO,message,sizeof(message));
    if(send_count >= 5)
    {
        exit(0);
    }
}
int main()
{
    printf("Exercise 3|| Siguser\n");
    pid_t pid = fork();

    if(pid == 0)
    {
        /*Child process*/
        signal(SIGUSR1,Siguser_handler);    
        while (1);
    }
    else
    {
        sleep(1);
        /*Parent Pid*/
        printf(" parent PID : %d\n",getpid());

        for(int i=0;i<5;i++)
        {
            kill(pid,SIGUSR1);
            sleep(2);
        }   

        wait(NULL);

    }

    return 0;
}