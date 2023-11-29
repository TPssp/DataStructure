#include <iostream>
#define MAXSIZE 255
#define OK 1
typedef int ElemType;
typedef int Status;
typedef struct
{
    int i, j;
    ElemType e;
} Triple;

typedef struct{
    Triple data[MAXSIZE+1];
    int mu,nu,tu;
}TSMatrix;


Status TransposeSMatrix(TSMatrix M, TSMatrix &T)
{
    int p, q, col;
    T.mu = M.nu;
    T.nu = M.mu;
    T.tu = M.tu;
    if (T.tu)
    {
        q = 1;
        for (col = 1; col <= M.nu; ++col)
            for (p = 1; p <= M.tu; ++p)
                if (M.data[p].j == col)
                {
                    T.data[q].i = M.data[p].j;
                    T.data[q].j = M.data[p].i;
                    T.data[q].e = M.data[p].e;
                    ++q;
                }
    }
    return OK;
}

