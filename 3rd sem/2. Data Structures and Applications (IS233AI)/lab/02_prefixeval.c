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

int main()
{
    char pref[SIZE];
    printf("Enter pref expr: ");
    scanf("%s", pref);
    int a = evalPref(pref);
    printf("%d", a);
}
