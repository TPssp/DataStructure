#include <stdio.h>
#include <stdlib.h>
#define Stack_INIT_SIZE 100
#define STACKINCRREMENT 10
#define OVERFLOW 1
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
typedef int Status;
typedef int SElemType;

typedef struct SNode
{
    SElemType data;
    struct SNode *next;
} SNode, *LinkStack;

void InitStack(LinkStack &S)
{
    S = (SNode *)malloc(sizeof(SNode));
    if (!S)
        exit(OVERFLOW);
    S->next = NULL;
}

void Push(LinkStack &S,SElemType e){
    SNode *p=(SNode*)malloc(sizeof(SNode));
    p->data=e;
    p->next=S->next;
    S->next=p;
}

void Pop(LinkStack &S, SElemType &e){
    if (S->next == NULL) return; // 如果栈为空，直接返回
    SNode *p = S->next; // 创建临时节点指针，指向栈顶元素
    e = p->data; // 将栈顶元素的数据赋值给e
    S->next = p->next; // 将栈顶指针移动到下一个节点
    free(p); // 释放临时节点指针所指向的内存
}
