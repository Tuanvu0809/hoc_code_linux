#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <time.h>
#include "inc/thread_mutex_cond.h"

data_type check = {
    .data_ready = false
};

pthread_mutex_t lock;
pthread_cond_t cond;

int main(){
    printf("Exercise 3|| Thread mutex and cond\n"); 

    srand(time(NULL));
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond,NULL);

    pthread_t producer, consumer; 
    int quanlity = 10;
  
    pthread_create(&producer,NULL,Producer,&quanlity);
    sleep(1);
    pthread_create(&consumer,NULL,Consumer,NULL);

    pthread_join(producer,NULL);
    pthread_join(consumer,NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
   
    return 0;
}