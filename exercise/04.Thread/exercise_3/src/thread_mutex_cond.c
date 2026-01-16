#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <time.h>
#include "../inc/thread_mutex_cond.h"

extern data_type check;

extern pthread_mutex_t lock;
extern pthread_cond_t cond;

void Randdom_number(int *array,int quanlity)
{       

        for(int i = 0; i < quanlity; ++i)
        {
            array[i] = rand()%100;

        }   
}     

void *Consumer( void *arg)
{
    
    printf("\n ====Consumer thread===\n");
    pthread_mutex_lock(&lock);

    while (check.data_ready == false) 
    {   
        pthread_cond_wait(&cond, &lock);
    }

    for (int i = 0; i < check.size; i++) 
    {
        printf("Consumer got data %d = %d\n", i, check.data[i]);
    }

    pthread_mutex_unlock(&lock);
    return NULL;
}

void *Producer( void *arg)
{
    int need = *(int *)arg;

    printf("\n ====Producer thread==\n");
    pthread_mutex_lock(&lock);

    Randdom_number(check.data,need);
    check.data_ready = true;
    check.size = need;

    for(int i= 0; i<  check.size ; i++)
    {
        printf("producer got data %d = %d\n", i,check.data[i]);
    }    

    pthread_cond_signal(&cond); 
    pthread_mutex_unlock(&lock);
    return NULL;
}