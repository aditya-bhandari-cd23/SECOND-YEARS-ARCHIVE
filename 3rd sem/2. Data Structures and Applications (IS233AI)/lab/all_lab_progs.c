// inftopostf

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define SIZE 20

typedef struct {
    char arr[SIZE];
    int top;
} Stack;

void push(Stack* s, char c)
{
    s->arr[++s->top] = c;
}

int pop(Stack* s)
{
    return s->arr[s->top--];
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
        default:
            printf("Invalid!");
            exit(0);
    }
}

void infToPostf(char inf[])
{
    int i;
    char symbol, temp;
    Stack s;
    s.top = -1;

    for (i = 0; inf[i] != '\0'; i++) {
        symbol = inf[i];
        if (isalpha(symbol))
            putchar(symbol);
        else if (symbol == '(')
            push(&s, symbol);
        else if (symbol == ')')
            while ((temp = pop(&s)) != '(')
                putchar(temp);
        else {
            while (s.top != -1 && s.arr[s.top] != '(' && preced(symbol) < preced(s.arr[s.top]))
                putchar(pop(&s));
            push(&s, symbol);
        }
    }
    while (s.top != -1)
        putchar(pop(&s));
}

int main1()
{
    char inf[SIZE];
    printf("Enter infix expr: ");
    scanf("%s", inf);
    infToPostf(inf);
}







// pref eval

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#define SIZE 20

typedef struct {
    float arr[SIZE];
    int top;
} Stack;

void push(Stack* s, float c)
{
    s->arr[++s->top] = c;
}

float pop(Stack* s)
{
    return s->arr[s->top--];
}

float operate(float a, float b, char op)
{
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '^':
            return pow(a, b);
        default:
            printf("Invalid");
            exit(0);
    }
}

float evalPref(char pref[])
{
    int i;
    float a, b;
    char symbol;
    Stack s;
    s.top = -1;
    for (i = strlen(pref) - 1; i >= 0; i--) {
        symbol = pref[i];
        if (isdigit(symbol))
            push(&s, symbol - '0');
        else {
            a = pop(&s);
            b = pop(&s);
            push(&s, operate(a, b, symbol));
        }
    }
    return i = pop(&s);
}

int main2()
{
    char pref[SIZE];
    printf("Enter pref expr: ");
    scanf("%s", pref);
    int a = evalPref(pref);
    printf("%d", a);
}







// q msg

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

int main3()
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







// poly mul

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

int main4()
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







// cll q

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

int main5()
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







// hashing

#include <stdio.h>
#define TABLE_SIZE 10
#define PRIME 7
int hash[TABLE_SIZE];

int hash1(int key)
{
    return key % TABLE_SIZE;
}

int hash2(int key)
{
    return PRIME - (key % PRIME);
}

void initHash()
{
    for (int i = 0; i < TABLE_SIZE; i++)
        hash[i] = -1;
}

void insert(int key)
{
    int idx = hash1(key), step = hash2(key), i, new_index;
    for (i = 0; i < TABLE_SIZE; i++) {
        new_index = (idx + i * step) % TABLE_SIZE;
        if (hash[new_index] == -1) {
            hash[new_index] = key;
            return;
        }
    }
    printf("Table Full!");
}

int search(int key)
{
    int idx = hash1(key);
    int step = hash2(key);
    int i, new_index;
    for (i = 0; i < TABLE_SIZE; i++) {
        new_index = (idx + i * step) % TABLE_SIZE;
        if (hash[new_index] == -1)
            break;
        if (hash[new_index] == key)
            return new_index;
    }
    return -1;
}

void delete(int key)
{
    int i = search(key);
    if (i == -1)
        printf("Not found");
    else
        hash[i] = -1;
}

void printhash()
{
    int i;
    for (i = 0; i < TABLE_SIZE; i++)
        if (hash[i] == -1)
            printf("Empty at index %d\n", i);
        else
            printf("%d at index %d\n", hash[i], i);
}

int main6()
{
    int choice, key;
    initHash();
    printf("1. Insert  2. Search  3. Delete  4. Display  5. Exit");
    while (1) {
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter key: ");
            scanf("%d", &key);
            insert(key);
            break;
        case 2:
            printf("Enter key: ");
            scanf("%d", &key);
            key = search(key);
            if (key == -1)
                printf("Not found");
            else
                printf("Found at %d", key);
            break;
        case 3:
            printf("Enter key: ");
            scanf("%d", &key);
            delete(key);
            break;
        case 4:
            printhash();
        }
    }
}







// pq
#include <stdio.h>
#define SIZE 20

void heapify(int arr[], int n)
{
    int i, v, k, j;
    for (i = n / 2; i > 0; i--) {
        k = i;
        v = arr[k];
        while (k * 2 <= n) {
            j = k * 2;
            if (j < n && arr[j] < arr[j + 1])
                j++;
            if (v < arr[j]) {
                arr[k] = arr[j];
                k = j;
            }
            else
                break;
        }
        arr[k] = v;
    }
}

int main7()
{
    int choice, n, i, arr[SIZE];
    printf("1. Createheap  2. Extractmax  3. Exit");
    while (1) {
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter no of elements: ");
            scanf("%d", &n);
            for (i = 1; i <= n; i++)
                scanf("%d", &arr[i]);
            heapify(arr, n);
            printf("After heapify:\n");
            for (i = 1; i <= n; i++)
                printf("%d ", arr[i]);
            break;
        case 2:
            if (n > 1) {
                printf("Max: %d", arr[1]);
                arr[1] = arr[n--];
                heapify(arr, n);
            }
            else
                printf("Empty!");
            break;
        case 3:
            return 0;
        }
    }
}







// expr tree

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

int main8()
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







// bintree

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int val)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->left = temp->right = NULL;
    temp->val = val;
    return temp;
}

void insertLeft(Node* root, int val)
{
    Node* temp = createNode(val);
    root->left = temp;
}

void insertRight(Node* root, int val)
{
    Node* temp = createNode(val);
    root->right = temp;
}

void inorder(Node* root)
{
    if (root) {
        inorder(root->left);
        printf("%d", root->val);
        inorder(root->right);
    }
}

int countNodes(Node* root)
{
    if (!root)
        return 0;
    return countNodes(root->left) + countNodes(root->right) + 1;
}

int countLeafNodes(Node* root)
{
    if (!root)
        return 0;
    if (!root->left && !root->right)
        return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

int countNonLeafNodes(Node* root)
{
    return countNodes(root) - countLeafNodes(root);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(Node* root)
{
    if (!root)
        return 0;
    return max(height(root->left), height(root->right));
}

int main9()
{
    Node* root = createNode(0);
    insertLeft(root, 1);
    insertRight(root, 2);
    insertRight(root->left, 3);
    insertLeft(root->right, 4);
    inorder(root);
}







// bst

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node* left;
    struct Node* right;
};

typedef struct Node Node;

Node* createNode(int val)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->val = val;
    temp->left = temp->right = NULL;
    return temp;
}

Node* insert(Node* root, int val)
{
    if (!root)
        return createNode(val);
    else if (root->val > val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

void preorder(Node* root)
{
    if (root) {
        printf("%d", root->val);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(Node* root)
{
    if (root) {
        inorder(root->left);
        printf("%d", root->val);
        inorder(root->right);
    }
}

void postorder(Node* root)
{
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d", root->val);
    }
}

Node* inorderSuccessor(Node* root)
{
    Node* temp = root;
    while (temp->left)
        temp = temp->left;
    return temp;
}

Node* delete(Node* root, int val)
{
    Node* temp;
    if (val < root->val)
        root->left = delete(root->left, val);
    if (val > root->val)
        root->right = delete(root->right, val);

    if (!root->left) {
        temp = root->right;
        free(root);
        return temp;
    }
    if (!root->right) {
        temp = root->left;
        free(root);
        return temp;
    }
    temp = inorderSuccessor(root->right);
    root->val = temp->val;
    root->right = delete(root->right, temp->val);
    return root;
}

int main10()
{
    int choice, val;
    Node* root = NULL;
    printf("1. Insert  2. Delete  3. Preorder  4. Inorder  5. Postorder");
    while (1) {
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter element to insert: ");
            scanf("%d", &val);
            root = insert(root, val);
            break;
        case 2:
            printf("Enter element to delete: ");
            scanf("%d", &val);
            root = delete(root, val);
            break;
        case 3:
            preorder(root);
            break;
        case 4:
            inorder(root);
            break;
        case 5:
            postorder(root);
            break;
        }
    }
}








int main()
{
    
}
