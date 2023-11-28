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

typedef struct
{
    int i;
} SElemType;

typedef struct
{
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;

Status InitStack(SqStack &S)
{
    S.base = (SElemType *)malloc(sizeof(SElemType) * Stack_INIT_SIZE);
    if (!S.base)
        exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = Stack_INIT_SIZE;
    return OK;
}

Status Push(SqStack &S, SElemType e)
{
    if (S.top - S.base >= S.stacksize)
    {
        S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCRREMENT) * sizeof(SElemType));
        if (!S.base)
            exit(OVERFLOW);
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCRREMENT;
    }

    *S.top = e;
    S.top++;
    //*S.top++=e;

    return OK;
}

Status Pop(SqStack &S,SElemType &e){
    if(S.top==S.base)
    return ERROR;
    else{
        e=*(S.top-1);
        S.top--;
        return OK;
    }
}

Status DestroyStack(SqStack &S) {
    free(S.base);
    S.base = S.top = NULL;
    S.stacksize = 0;
    return OK;
}

Status ClearStack(SqStack &S) {
    S.top = S.base;
    return OK;
}

Status StackEmpty(SqStack S) {
    return S.top == S.base ? TRUE : FALSE;
}

int StackLength(SqStack S) {
    return S.top - S.base;
}

Status GetTop(SqStack S, SElemType &e) {
    if (S.top == S.base)
        return ERROR;  // 栈空
    e = *(S.top - 1);
    return OK;
}

typedef void (*VisitFunc)(SElemType);

void visit(SElemType e) {
    // 这里是你要在遍历时执行的操作
    printf("%d ", e.i);
}

Status StackTraverse(SqStack S, VisitFunc visit) {
    SElemType *p = S.base;
    while (p < S.top) {
        visit(*p);
        p++;
    }
    printf("\n");
    return OK;
}
