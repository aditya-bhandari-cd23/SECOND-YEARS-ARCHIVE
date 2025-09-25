#include<stdio.h>
#include<string.h>
#define SIZE 20

typedef struct {
    char data[20][SIZE];
    int front, rear;
} Queue;

void init(Queue* q)
{
    q->front = -1;
    q->rear = -1;
}

void send(Queue* q, char msg[])
{
    if ((q->front - q->rear) % SIZE == 1)
        printf("Full!");
    else {
        if (q->front == -1)
            q->front++;
        q->rear = (q->rear + 1) % SIZE;
        strcpy(q->data[q->rear], msg);
    }
}

void receive(Queue* q)
{
    char msg[20];
    if (q->front == -1 && q->rear == -1)
        printf("Empty!");
    strcpy(msg, q->data[q->front]);
    q->front = (q->front + 1) % SIZE;
    if (q->front == q->rear)
        q->front = q->rear = -1;
    printf("%s", msg);
}

void display_(Queue* q)
{
    int i;
    if (q->front == -1)
        printf("Empty!");
    else {
        for (i = q->front; i != q->rear; i = (i + 1) % SIZE)
            printf("%s", q->data[i]);
        printf("%s", q->data[i]);
    }
}

int main()
{
    int c;
    char msg[20];
    Queue q;
    init(&q);

    printf("1. Send\t2. Receive\t3. Display\t4.Exit\n");
    while (1) {
        scanf("%d", &c);
        switch (c) {
        case 1:
            printf("Enter msg: ");
            scanf("%s", msg);
            send(&q, msg);
            break;
        case 2:
            printf("Received: ");
            receive(&q);
            break;
        case 3:
            display_(&q);
            break;
        case 4:
            return 0;
        }
    }
}
