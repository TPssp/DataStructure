#include <iostream>
#include <stdio.h>
#define MAXSIZE 255
#define OK 1
typedef int ElemType;
typedef int AtomType;

typedef enum
{
    ATOM,
    LIST
} ElemTag;

typedef struct GLNode
{
    ElemTag tag;
    union
    {
        AtomType atom;
        struct
        {
            struct GLNode *hp, *tp;
        } ptr;
    };
}*Glist;