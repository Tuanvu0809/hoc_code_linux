#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static int g_variable_demo = 0;

pthread_rwlock_t rw_lock;   

void *Reader(void *arg)
{
    pthread_rwlock_rdlock(&rw_lock);
    int index = *(int*) arg;
    printf("Data read at %d value = %d\n",index,g_variable_demo);
    sleep(5);
    pthread_rwlock_unlock(&rw_lock);
    return NULL;
}
void *Writer(void *arg)
{
    pthread_rwlock_wrlock(&rw_lock);
    int index = *(int *) arg;
    g_variable_demo ++;
    printf("Data wirte at %d update value = %d\n",index,g_variable_demo);
    sleep(2);
    pthread_rwlock_unlock(&rw_lock);
    return NULL;
}

int main()
{
    pthread_rwlock_init(&rw_lock,NULL);
    pthread_t reader_1,reader_2,reader_3,reader_4,reader_5;
    pthread_t writer_1,writer_2;
    int id_1= 1 ,id_2= 2 ,id_3= 3 ,id_4= 4 ,id_5= 5 ;
    int index_1 =1 , index_2 = 2;

    pthread_create(&writer_1,NULL,Writer,&index_1);
    pthread_create(&writer_2,NULL,Writer,&index_2);
    sleep(1);
    pthread_create(&reader_1,NULL,Reader,&id_1);
    pthread_create(&reader_2,NULL,Reader,&id_2);
    pthread_create(&reader_3,NULL,Reader,&id_3);
    pthread_create(&reader_4,NULL,Reader,&id_4);
    pthread_create(&reader_5,NULL,Reader,&id_5);

    pthread_join(writer_1,NULL);
    pthread_join(writer_2,NULL);

    pthread_join(reader_1,NULL);
    pthread_join(reader_2,NULL);
    pthread_join(reader_3,NULL);
    pthread_join(reader_4,NULL);
    pthread_join(reader_5,NULL);

    pthread_rwlock_destroy(&rw_lock);
    
    return 0;
}