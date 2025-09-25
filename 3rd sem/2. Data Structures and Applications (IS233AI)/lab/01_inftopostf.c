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

int main()
{
    char inf[SIZE];
    printf("Enter infix expr: ");
    scanf("%s", inf);
    infToPostf(inf);
}
