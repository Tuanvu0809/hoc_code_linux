#ifndef MUTEX_COND_H
#define MUTEX_COND_H

typedef struct data_type{
    int data[10];
    int size;
    bool data_ready;
}data_type;

void Randdom_number(int *array,int quanlity);
void *Consumer( void *arg);
void *Producer( void *arg);

#endif
