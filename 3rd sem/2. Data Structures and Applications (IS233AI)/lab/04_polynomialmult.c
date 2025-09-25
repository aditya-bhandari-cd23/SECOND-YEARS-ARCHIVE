#include<stdio.h>
#include<malloc.h>

struct Node {
    int co;
    int po;
    struct Node* next;
};

typedef struct Node Node;

Node* append(Node* head, int co, int po)
{
    Node* curr = head;
    Node* temp = (Node*) malloc(sizeof(Node));
    temp->co = co;
    temp->po = po;
    temp->next = NULL;
    
    if (!head)
        return temp;
    while (curr->next)
        curr = curr->next;
    curr->next = temp;
    return head;
}

Node* addNode(Node* head, int co, int po)
{
    Node* curr = head;
    while (curr) {
        if (curr->po == po) {
            curr->co += co;
            return head;
        }
        curr = curr->next;
    }
    head = append(head, co, po);
    return head;
}

Node* multiply(Node* p1, Node* p2)
{
    Node* c1 = p1, * c2 = p2;
    Node* p3 = NULL;
    while (c1) {
        while (c2) {
            p3 = addNode(p3, c1->co * c2->co, c1->po + c2->po);
            c2 = c2->next;
        }
        c1 = c1->next;
    }
    return p3;
}

void display(Node* head)
{
    Node* curr = head;
    while (curr) {
        printf("%dx^%d + ", curr->co, curr->po);
        curr = curr->next;
    }
}

int main()
{
    int n1, n2, i, co, po;
    Node* p1 = NULL, * p2 = NULL, * p3 = NULL;

    printf("Enter no of terms of 1st poly: ");
    scanf("%d", &n1);
    for (i = 0; i < n1; i++) {
        printf("Enter co & po of 1st poly: ");
        scanf("%d%d", &co, &po);
        p1 = addNode(p1, co, po);
    }
    printf("First poly: ");
    display(p1);

    printf("Enter no of terms of 2nd poly: ");
    scanf("%d", &n2);
    for (i = 0; i < n2; i++) {
        printf("Enter co & po of 2nd poly: ");
        scanf("%d%d", &co, &po);
        p2 = addNode(p2, co, po);
    }
    printf("Second poly: ");
    display(p2);

    p3 = multiply(p1, p2);
    printf("Multiplied polynomial: ");
    display(p3);
}
