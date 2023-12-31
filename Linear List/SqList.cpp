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

typedef struct
{
    char name[8];
    int age;
    char sex[2];
    float score;
} ElemType;

typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
} SqList;
  
Status InitList_Sq(SqList &L)
{
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem)
        exit(OVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
} //InitList_Sq

Status DestoryList(SqList &L)
{
    free(L.elem);
    return OK;
} //DestoryList

Status ListEmpty(SqList L)
{
    if (L.length == 0)
        return TRUE;
    else
        return FALSE;
} //ListEmpty

Status ListLength(SqList L)
{
    return L.length;
} //ListLength

Status PriorElem(SqList L, int cur_e, ElemType &pre_e)
{
    if (cur_e <= 0 || L.length == 0 || cur_e > L.length)
        return ERROR;
    else
        pre_e = L.elem[cur_e - 1];
        return OK;
} //PriorElem

Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
    if (i < 1 || i > L.length + 1)
        return ERROR;
    if (L.length >= L.listsize)
    {
        ElemType *newbase = (ElemType *)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            exit(OVERFLOW);
        else
        {
            L.elem = newbase;
            L.listsize += LISTINCREMENT;
        }
    }

    ElemType *q = &L.elem[i - 1];
    ElemType *p = &L.elem[L.length - 1];
    for (; p >= q; --p)
    {
        *(p + 1) = *p;
    }
    *q = e;
    ++L.length;
    return OK;
} //ListInsert_Sq

Status ListDelete_Sq(SqList &L, int i, ElemType &e)
{
    if (i < 1 || i > L.length)
        return ERROR;
    ElemType *q = &L.elem[i - 1];
    e = *q;
    ElemType *p = &L.elem[L.length - 1];
    for (++q; q <= p; ++q)
    {
        *(q - 1) = *q;
    }
    --L.length;
    return OK;
} //ListDelete_Sq

int LocateElem_Sq(SqList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
    int i = 1;
    ElemType *p = L.elem;
    while (i <= L.length && !(*compare)(*p++, e))
    {
        ++i;
    }
    if (i <= L.length)
        return i;
    else
        return 0;
} //LocateElem_Sq

Status compare(ElemType a, ElemType b)
{
    if (strcmp(a.name, b.name) != 0)
    {
        return FALSE;
    }
    if (a.age != b.age)
    {
        return FALSE;
    }
    if (strcmp(a.sex, b.sex) != 0)
    {
        return FALSE;
    }
    if (fabs(a.score - b.score) > 1e-6)
    {
        return FALSE;
    }
    return TRUE;
} //compare

int main()
{
    //创建新表
    SqList L;
    InitList_Sq(L);

    ElemType e = {"lzy", 19, "x", 0};
    ElemType f = {"zyf", 18, "y", 1};
    //插入值
    ListInsert_Sq(L,1,e);
    ListInsert_Sq(L,2,f);

    //求前驱的值
    ElemType k;
    PriorElem(L,2,k);
    int length_before = ListLength(L);
    printf("Length Before Delete = %d\n",length_before);
    printf("%d",k.age);

    //删除值
    ElemType d;
    ListDelete_Sq(L,1,d);
    int length_after = ListLength(L);
    printf("Length After Delete = %d\n",length_after);
    
    //定位值
    int i = LocateElem_Sq(L,e,compare);
    printf("%d\n",i);

    //销毁表
    DestoryList(L);
    return 0;
}
