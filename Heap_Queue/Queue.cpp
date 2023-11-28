#include <iostream>
#define OVERFLOW 1
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
typedef int QElemType;
typedef int Status;

typedef struct QNode
{
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct
{
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;

LinkQueue Q;

Status InitQueue(LinkQueue &Q)
{
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode)); // QueuePtr能写成QNode*吗？
    if (!Q.front)
    {
        exit(OVERFLOW);
    }
    Q.front->next = NULL;
    return OK;
}

Status EnQueue(LinkQueue &Q, QElemType e)
{
    QNode *p = (QNode *)malloc(sizeof(QNode));
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}

Status DeQueue(LinkQueue &Q, QElemType &e)
{
    if (Q.front == Q.rear)
        return ERROR;
    QNode *p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)
        Q.rear = Q.front;
    free(p);
    return OK;
}
