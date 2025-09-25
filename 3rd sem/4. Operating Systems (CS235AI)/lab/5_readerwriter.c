// reader writer
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

sem_t mutex, wr;
int count, rcount;


void* writer(void* p)
{
    int* i = (int*)p;
    sem_wait(&wr);
    printf("Writer %d wrote %d\n", *i, ++count);
    sem_post(&wr);
}

void* reader(void* p)
{
    int* i = (int*)p;
    sem_wait(&mutex);
    if (++rcount == 1)
        sem_wait(&wr);
    sem_post(&mutex);
    printf("Reader %d read %d\n", *i, count);
    sem_wait(&mutex);
    if (--rcount == 0)
        sem_post(&wr);
    sem_post(&mutex);
}

int main()
{
    pthread_t p[6];
    int arr[] = {1,2,3,1,2,3};
    sem_init(&mutex, 0, 1);
    sem_init(&wr, 0, 1);
    count = 0;
    rcount = 0;

    for (int i = 0; i < 3; i++)
        pthread_create(&p[i], NULL, writer, (void*)&arr[i]);
    for (int i = 3; i < 6; i++)
        pthread_create(&p[i], NULL, reader, (void*)&arr[i]);
    for (int i = 0; i < 6; i++)
        pthread_join(p[i], NULL);
}