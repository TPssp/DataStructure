#include <stdio.h>
#include <stdlib.h>
#include <cassert>
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

void testInitStack() {
    SqStack S;
    assert(InitStack(S) == OK);
    assert(S.base != NULL);
    assert(S.top == S.base);
    assert(S.stacksize == Stack_INIT_SIZE);
    DestroyStack(S);
}

void testPush() {
    SqStack S;
    InitStack(S);
    SElemType e = {1};
    assert(Push(S, e) == OK);
    assert(S.top == S.base + 1);
    assert(S.base[0].i == 1);
    DestroyStack(S);
}

void testPop() {
    SqStack S;
    InitStack(S);
    SElemType e = {1};
    Push(S, e);
    assert(Pop(S, e) == OK);
    assert(e.i == 1);
    assert(S.top == S.base);
    DestroyStack(S);
}

void testDestroyStack() {
    SqStack S;
    InitStack(S);
    assert(DestroyStack(S) == OK);
    assert(S.base == NULL);
    assert(S.top == NULL);
    assert(S.stacksize == 0);
}

void testClearStack() {
    SqStack S;
    InitStack(S);
    SElemType e = {1};
    Push(S, e);
    assert(ClearStack(S) == OK);
    assert(S.top == S.base);
    DestroyStack(S);
}

void testStackEmpty() {
    SqStack S;
    InitStack(S);
    assert(StackEmpty(S) == TRUE);
    SElemType e = {1};
    Push(S, e);
    assert(StackEmpty(S) == FALSE);
    DestroyStack(S);
}

void testStackLength() {
    SqStack S;
    InitStack(S);
    assert(StackLength(S) == 0);
    SElemType e = {1};
    Push(S, e);
    assert(StackLength(S) == 1);
    DestroyStack(S);
}

void testGetTop() {
    SqStack S;
    InitStack(S);
    SElemType e = {1};
    Push(S, e);
    assert(GetTop(S, e) == OK);
    assert(e.i == 1);
    DestroyStack(S);
}

void testStackTraverse() {
    SqStack S;
    InitStack(S);
    SElemType e1 = {1};
    SElemType e2 = {2};
    Push(S, e1);
    Push(S, e2);
    printf("Expected output: 1 2\n");
    StackTraverse(S, visit);
    DestroyStack(S);
}

int main() {
    testInitStack();
    testPush();
    testPop();
    testDestroyStack();
    testClearStack();
    testStackEmpty();
    testStackLength();
    testGetTop();
    testStackTraverse();
    return 0;
}