// pthreads

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>

int a[4][4], b[4][4];

void* mult(void* p)
{
    int* k = (int*)p;
    int i, j;
    for (i = 0; i < 4; i++)
        b[*k][i] = a[*k][i];
    for (i = 0; i < 4; i++)
        for (j = 0; j < *k; j++)
            b[*k][i] *= a[*k][i];
    return NULL;
}

int main()
{
    pthread_t p[4];
    int i, j;
    printf("Enter matrix: ");
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            scanf("%d", &a[i][j]);
    printf("Your matrix: ");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
    
    for (i = 0; i < 4; i++) {
        int* arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&p[i], NULL, mult, arg); 
    }
    for (i = 0; i < 4; i++)
        pthread_join(p[i], NULL);
    
    printf("New matrix: ");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++)
            printf("%d ", b[i][j]);
        printf("\n");
    }
}