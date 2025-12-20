#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void *Thread_dosomthing( void *index )
{
    printf("Thread Index %d\n",*(int *)index);
    printf("Get PID Thread %d\n",getpid());
    return NULL;
}

int main(){
    printf("Exercise 1|| Thread\n"); 

    printf("Get PID main %d\n",getpid());
    pthread_t thread1,thread2;
    int index1 = 1;
    int index2 = 2;

    pthread_create(&thread1,NULL,Thread_dosomthing,&index1);
    pthread_create(&thread2,NULL,Thread_dosomthing,&index2);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    return 0;
}