#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void Sig_int_handler(int sig)
{
    printf("\nSIGINT received\n");
}
void Sig_term_handler(int sig)
{
    printf("\nSIGTERM received\n exit program\n");

    exit(0);
}

int main()
{
    printf("Exercise 4|| select and poll\n");
    struct pollfd mypoll;
    char buf[50];

    signal( SIGINT,Sig_int_handler);
    signal( SIGTERM,Sig_term_handler);

    memset(&mypoll,0,sizeof(struct pollfd ));
    mypoll.fd =  STDIN_FILENO	;
    mypoll.events =  POLLIN	;

    while (1)
    {
        int result = poll(&mypoll,1,-1);
        memset(buf, 0, sizeof(buf));
        ssize_t n; 

        if(result == -1 )
        {
                if (errno == EINTR)
                {
                    continue;
                }
            perror("fail \n");

        }
        else
        {
            if(mypoll.revents & POLLIN)
            {
                n = read(STDIN_FILENO,buf,sizeof(buf) - 1);
            }

        }

        if(n>0)
        {
            write(STDOUT_FILENO, buf, sizeof(buf) - 1);
        }
        else {
            
            write(STDOUT_FILENO,"Nothing", sizeof("Nothing") - 1);

        }
    }

    return 0;
}
