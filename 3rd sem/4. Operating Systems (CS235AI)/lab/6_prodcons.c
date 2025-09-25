// producer consumer
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#define SIZE 10

int arr[SIZE], count;
pthread_mutex_t mutex;
sem_t empty, full;
pthread_t pprod[SIZE], pcons[SIZE];

void* producer(void* p)
{
    int item = rand() % 5;
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    arr[count++] = item;
    printf("Producer produced item: %d\n", item);
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
}

void* consumer(void* p)
{
    int item;
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    item = arr[--count];
    printf("Consumer consumed item: %d\n", item);
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
}

int main()
{
    int i, n1, n2;
    count = 0;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 1, SIZE);
    sem_init(&full, 1, 0);

    printf("Enter no of producers: ");
    scanf("%d", &n1);
    printf("Enter no of consumers: ");
    scanf("%d", &n2);
    for (i = 0; i < n1; i++)
        pthread_create(&pprod[i], NULL, producer, NULL);
    for (i = 0; i < n2; i++)
        pthread_create(&pcons[i], NULL, consumer, NULL);
    for (i = 0; i < n1; i++)
        pthread_join(pprod[i], NULL);
    for (i = 0; i < n2; i++)
        pthread_join(pcons[i], NULL);
}