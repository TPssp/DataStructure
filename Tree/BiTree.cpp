#include <iostream>
using namespace std;
#define OVERFLOW 0
#define OK 1
#define STACK_INIT_SIZE 100
#define INCREMENT 10
#define ERROR 0
#define FALSE 0
#define TRUE 1

typedef int Status;
typedef char TElemType;


typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

BiTree x;

typedef BiTree SElemType;

typedef struct
{
    SElemType *base;
    SElemType *top;
    int stacksize;
} STACK;

void InitStack(STACK &S)
{
    S.base = (SElemType *)malloc(sizeof(SElemType) * STACK_INIT_SIZE);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
}

Status Push(STACK &S, SElemType e)
{ // 入栈
    if (S.top - S.base >= S.stacksize)
    { // 栈满，追加存储空间
        S.base = (SElemType *)realloc(S.base, (S.stacksize + INCREMENT) * sizeof(SElemType));
        if (!S.base)
            exit(OVERFLOW); // 存储分配失败
        S.top = S.base + S.stacksize;
        S.stacksize += INCREMENT;
    }
    *S.top++ = e;
    return OK;
}

Status Pop(STACK &S, SElemType &e)
{ // 出栈
    // 若栈不空，则删除S的栈顶元素，
    // 用e返回其值，并返回OK；
    // 否则返回ERROR
    if (S.top == S.base)
        return ERROR;
    e = *--S.top;
    return OK;
}

Status StackEmpty(STACK S)
{
    if (S.base == S.top)
    {
        return TRUE;
    }
    else
        return FALSE;
}

Status CreatBiTree(BiTree &T)
{
    TElemType ch;
    cin >> ch;
    if (ch == '^')
    {
        T = NULL;
    }
    else
    {
        T = (BiTNode *)malloc(sizeof(BiTNode));
        if (!T)
        {
            exit(OVERFLOW);
        }
        // if (!(T = (BiTNode *)malloc(sizeof(BiTNode))))
        //  exit(OVERFLOW);
        T->data = ch;
        CreatBiTree(T->lchild);
        CreatBiTree(T->rchild);
    }
    return OK;
}

void Preorder(BiTree T, void (*visit)(TElemType &e))
{
    if (T)
    {
        visit(T->data);
        Preorder(T->lchild, visit);
        Preorder(T->rchild, visit);
    }
}

void InOrder(BiTree T, void (*visit)(TElemType &e))
{
    if (T)
    {
        InOrder(T->lchild, visit);
        visit(T->data);
        InOrder(T->rchild, visit);
    }
}

void PostOrder(BiTree T, void (*visit)(TElemType &e))
{
    if (T)
    {
        PostOrder(T->lchild, visit);
        PostOrder(T->rchild, visit);
        visit(T->data);
    }
}

void visit(TElemType &e)
{
    printf("%c", e);
}

// Status InorderTraverse(BiTree T,void(*visit)(TElemType e)){
//     STACK S;
//     InitStack(S);
//     BiTree p=T;
//     while(p||!StcakEmpty(S)){
//         if(p){
//             Push(S,p);
//             p=p->lchild;
//         }
//         else{
//             Pop(S,p);
//             p=p->rchild;
//         }
//     }
//     return OK;
// }

BiTNode *GoFarLeft(BiTree T, STACK &S)
{
    if (!T)
        return NULL;
    while (T->lchild)
    {
        Push(S, T);
        T = T->lchild;
    }
    return T;
}

void Inorder_I(BiTree T, void (*visit)(TElemType &e))
{
    STACK S;
    BiTree t = GoFarLeft(T, S);
    while (t)
    {
        visit(t->data);
        if (t->rchild)
        {
            t = GoFarLeft(t->rchild, S);
        }
        else if (!StackEmpty(S))
        {
            Pop(S, t);
        }
        else
            t = NULL;
    }
}

int main()
{
    BiTree T;
    CreatBiTree(T);

    Preorder(T, visit);
    printf("\n");

    InOrder(T, visit);
    printf("\n");

    PostOrder(T, visit);
    printf("\n");

    Inorder_I(T,visit);
}