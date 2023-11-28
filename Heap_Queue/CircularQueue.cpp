#include <iostream>
#define OVERFLOW 1
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define MAXQSIZE 100
typedef int QElemType;
typedef int Status;

typedef struct
{
    QElemType *base;
    int front;
    int rear;
} SqQueue;

SqQueue Sq;

Status InitQueue(SqQueue &Q)
{
    Q.base = (QElemType *)malloc(MAXQSIZE * sizeof(QElemType));
    if (!Q.base)
        exit(OVERFLOW);
    Q.front = Q.rear = 0;
    return OK;
}

Status EnQueue(SqQueue &Q, QElemType e)
{
    if ((Q.rear + 1) % MAXQSIZE == Q.front)
        return ERROR;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    return OK;
}

Status DeQueue(SqQueue &Q, QElemType &e)
{
    if (Q.front == Q.rear)
        return ERROR;
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
    return OK;
}

int QueueLength(SqQueue Q)
{
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

