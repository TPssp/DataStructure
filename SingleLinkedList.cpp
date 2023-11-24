#include <iostream>
#include <cmath>
#include <cstring>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define OVERFLOW 1
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
typedef int Status;

typedef struct ElemType{
    int a;
}ElemType;


typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;


//构造一个空的带头结点的线性表L
void InitList(LinkList &L){
    L=(LNode*)malloc(sizeof(LNode));
    L->next=NULL;
}

//判断线性表L是否为空
int ListEmpty(LinkList L){
    if(L->next==NULL)
        return TRUE;
    else
        return FALSE;
}


