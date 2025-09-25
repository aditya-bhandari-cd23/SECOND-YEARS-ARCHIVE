#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 20

struct Node {
    char val;
    struct Node* left;
    struct Node* right;
};

typedef struct Node Node;

typedef struct {
    Node* data[SIZE];
    int top;
} Stack;

void push(Stack* s, Node* c)
{
    s->data[++s->top] = c;
}

Node* pop(Stack* s)
{
    return s->data[s->top--];
}

Node* createNode(char c)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->val = c;
    temp->left = temp->right = NULL;
    return temp;
}

int preced(char op)
{
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
}

void preorder(Node* t)
{
    if (t) {
        printf("%c", t->val);
        preorder(t->left);
        preorder(t->right);
    }
}

void inorder(Node* t)
{
    if (t) {
        inorder(t->left);
        printf("%c", t->val);
        inorder(t->right);
    }
}

void postorder(Node* t)
{
    if (t) {
        postorder(t->left);
        postorder(t->right);
        printf("%c", t->val);
    }
}

Node* exprTree(char infix[])
{
    Node* temp, * t;
    Stack os, ts;
    os.top = -1;
    ts.top = -1;
    int i;
    char symbol;
    for (i = 0; infix[i] != '\0'; i++) {
        symbol = infix[i];
        temp = createNode(symbol);
        if (isalnum(symbol))
            push(&ts, temp);
        else {
            while (os.top != -1 && preced(os.data[os.top]->val) >= preced(symbol)) {
                t = pop(&os);
                t->right = pop(&ts);
                t->left = pop(&ts);
                push(&ts, t);
            }
            push(&os, temp);
        }
    }
    while (os.top != -1) {
        t = pop(&os);
        t->right = pop(&ts);
        t->left = pop(&ts);
        push(&ts, t);
    }

    return pop(&ts);
}

int main()
{
    char inf[SIZE];
    Node* temp;
    printf("Enter infix expr: ");
    scanf("%s", inf);
    temp = exprTree(inf);
    printf("\nPreorder: ");
    preorder(temp);
    printf("\nInorder: ");
    inorder(temp);
    printf("\nPostorder: ");
    postorder(temp);
}
