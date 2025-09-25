#include<stdio.h>
#include<stdlib.h>

struct CNode {
    int val;
    struct CNode* next;
};
typedef struct CNode CNode;

CNode* enq(CNode* last, int val)
{
    CNode* temp = (CNode*)malloc(sizeof(CNode));
    temp->val = val;
    if (!last) {
        last = temp;
        last->next = last;
    }
    else {
        temp->next = last->next;
        last->next = temp;
        last = temp;
    }
    return last;
}

CNode* deq(CNode* last)
{
    CNode* curr;
    if (!last) {
        printf("Empty!\n");
        return NULL;
    }
    curr = last->next;
    last->next = curr->next;
    printf("Dequeued %d\n", curr->val);
    free(curr);
    return last;
}

void displayQ(CNode* last)
{
    CNode* curr;
    if (!last) {
        printf("Empty!");
        return;
    }
    
    for (curr = last->next; curr != last; curr = curr->next)
        printf("%d ", curr->val);
    printf("%d\n", curr->val);
}

int main()
{
    int c, val;
    CNode* last = NULL;
    printf("1. Enq  2. Deq  3. Display  4. Exit");
    while (1) {
        scanf("%d", &c);
        switch (c) {

        case 1:
            printf("Enter element to enq: ");
            scanf("%d", &val);
            last = enq(last, val);
            break;

        case 2:
            last = deq(last);
            break;

        case 3:
            displayQ(last);
            break;

        case 4:
            return 0;
        }
    }
}
