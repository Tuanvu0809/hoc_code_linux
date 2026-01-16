#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

long long couter = 0;

pthread_mutex_t lock;
void *Increase_value(  )
{
    for(unsigned long int i =0 ;i < 1000000;i++)
    {
        pthread_mutex_lock(&lock);
        couter ++ ;
     pthread_mutex_lock(&lock);
    }
    return NULL;
}

int main(){
    printf("Exercise 2 || Thread mutex\n"); 

    pthread_t thread1,thread2,thread3;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&thread1,NULL,Increase_value,NULL);
    pthread_create(&thread2,NULL,Increase_value,NULL);
    pthread_create(&thread3,NULL,Increase_value,NULL);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    
    pthread_mutex_destroy(&lock);

    printf("\ncouter value = %lld\n",couter);

    return 0;
}