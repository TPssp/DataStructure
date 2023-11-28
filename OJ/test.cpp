#include <iostream>
#include <stdlib.h>
#include <string>
#include <cctype>
using namespace std;
#define OVERFLOW 1
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define STACK_INIT_SIZE 100
#define INCREMENT 10

typedef struct Stack
{
    char *base;
    char *top;
    // int stacksize;
} Stack;

typedef struct QNode
{
    char data;
    struct QNode *next;
} QNode;

typedef struct
{
    QNode *front;
    QNode *rear;
} LinkQueue;

void InitStack(Stack &S)
{
    S.base = (char *)malloc(sizeof(char) * STACK_INIT_SIZE);
    if (!S.base)
        exit(OVERFLOW);
    S.top = S.base;
}

void Push(Stack &S, char e)
{
    if (S.top - S.base >= STACK_INIT_SIZE)
    {
        S.base = (char *)realloc(S.base, sizeof(char) * (STACK_INIT_SIZE + INCREMENT));
        S.top = S.base + STACK_INIT_SIZE;
    }
    *S.top = e;
    S.top++;
}

void Pop(Stack &S, char &e)
{
    // if(S.base==S.top) return ERROR;
    e = *(S.top - 1);
    S.top--;
}

void InitQueue(LinkQueue &Q)
{
    Q.front = Q.rear = (QNode *)malloc(sizeof(QNode));
    if (!Q.front)
        exit(OVERFLOW);
    Q.front->next = NULL;
}

void EnQueue(LinkQueue &Q, char e)
{
    QNode *p = (QNode *)malloc(sizeof(QNode));
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
}

void DeQueue(LinkQueue &Q, char &e)
{
    QNode *p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)
        Q.front = Q.rear;
    free(p);
}

int main()
{
    int flag = 1;
    string s;
    getline(cin, s);
    int length = s.length();
    Stack S;
    InitStack(S);
    LinkQueue Q;
    InitQueue(Q);
    if (length % 2 == 0)
    {
        for (int i = 0; i < length / 2; i++)
        {
            Push(S, s[i]);
        }
        for (int i = (length / 2); i < length; i++)
        {
            EnQueue(Q, s[i]);
        }

        for (int i = 0; i < length / 2; i++)
        {
            char c, d;
            Pop(S, c);
            DeQueue(Q, d);
            if (c != d)
            {
                flag = 0;
            }
        }
    }

    if (length % 2 != 0)
    {
        for (int i = 0; i < length / 2; i++)
        {
            Push(S, s[i]);
        }
        for (int i = (length / 2) + 1; i < length; i++)
        {
            EnQueue(Q, s[i]);
        }

        for (int i = 0; i < length / 2; i++)
        {
            char c, d;
            Pop(S, c);
            DeQueue(Q, d);
            if (c != d)
            {
                flag = 0;
            }
        }
    }

    printf("%d", flag);
    return 0;
}