#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define RETURN_VALUE_PID    29
#define SLEEP_VALUE         5
#define DELAY_VALUE         1
int main()
{
    printf("Exercise 3.1 || Process \n ");
    printf("parent PID: %d \n",getpid());

    pid_t pid = fork();
    int status;

    if(pid == 0)
    {
        /*Child process*/
        printf("====Child====\n");
        printf("Parent PID: %d\n",getppid());
        printf("PID %d\n",getpid());
        printf("Value of PID: %d\n",pid);
        sleep(SLEEP_VALUE);
       
        exit(RETURN_VALUE_PID);
    }
    else {
      /*Process parent*/
        printf("\n====Parent====\n");
        printf("Parent PID: %d\n",getpid());
        printf("Value of PID: %d\n",pid);
       
        /*Wait process child end*/
        while(1)
        {
            pid_t check = waitpid(pid,&status,WNOHANG);

            if(check > 0 )
            {
                if (WIFEXITED(status)) 
                {
                    printf("Child exited normally\n");
                    printf("Exit status = %d\n", WEXITSTATUS(status));
                }
                break;
            }
            else if(check==0)
            {
                printf("----Child exits----\n");
            }
            else {
                perror("waitpid");
                break;
            }
           sleep(DELAY_VALUE);
        }
    }
    return 0;
}