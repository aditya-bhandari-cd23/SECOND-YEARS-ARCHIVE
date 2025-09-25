#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#define N 5
#define HUNGRY 0
#define EATING 1
#define THINKING 2
#define LEFT (phnum - 1) % N
#define RIGHT (phnum + 1) % N

int arr[N], phil[N] = {0,1,2,3,4};
sem_t s[N];
sem_t mutex;

void test(int phnum)
{
    if (arr[phnum] == HUNGRY && arr[LEFT] != EATING && arr[RIGHT] != EATING) {
        arr[phnum] = EATING;
        printf("Philosopher %d takes fork %d and %d\nPhilosopher %d is eating\n", phnum + 1, LEFT + 1, phnum + 1, phnum + 1);
        sem_post(&s[phnum]);
    }
}

void take_fork(int phnum)
{
    sem_wait(&mutex);
    arr[phnum] = HUNGRY;
    printf("Philosopher %d is hungry\n", phnum + 1);
    test(phnum);
    sem_post(&mutex);
    sem_wait(&s[phnum]);
}

void put_fork(int phnum)
{
    sem_wait(&mutex);
    arr[phnum] = THINKING;
    printf("Philosopher %d puts down forks %d and %d\nPhilosopher %d is thinking\n", phnum + 1, LEFT + 1, phnum + 1, phnum + 1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void* philosopher(void* p)
{
    while (1) {
        int* i = (int*) p;
        take_fork(*i);
        put_fork(*i);
    }
}

int main()
{
    int i;
    pthread_t p[N];
    for (i = 0; i < N; i++)
        sem_init(&s[i], 0, 0);
    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++) {
        pthread_create(&p[i], NULL, philosopher, (void*)&phil[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }
    for (i = 0; i < N; i++)
        pthread_join(p[i], NULL);
}