#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 50
#define STACKINCREMENT 10

typedef struct
{
    int *base;
    int *top;
    int stacksize;
} Stack;

void InitStack(Stack &S)
{
    S.base = (int *)malloc(sizeof(int) * STACK_INIT_SIZE);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
}

void Push(Stack &S, int e)
{
    *S.top = e;
    S.top++;
}

void Pop(Stack &S, int &e)
{
    e = *(S.top - 1);
    S.top--;
}

void Convert(int decimalnum, int base)
{
    Stack S;
    InitStack(S);

    while (decimalnum > 0)
    {
        int remainder = decimalnum % base;
        Push(S, remainder);
        decimalnum /= base;
    }

    int digit;

    if (S.top == S.base)
    {
        printf("0");
    }
    else
    {
        while (S.top > S.base)
        {
            Pop(S, digit);
            if (base == 16)
            {
                switch (digit)
                {
                case 10:
                    printf("A");
                    break;
                case 11:
                    printf("B");
                    break;
                case 12:
                    printf("C");
                    break;
                case 13:
                    printf("D");
                    break;
                case 14:
                    printf("E");
                    break;
                case 15:
                    printf("F");
                    break;
                default:
                    printf("%d", digit);
                }
            }
            else
                printf("%d", digit);
        }
    }
}

int main()
{
    int decimalnum, base;
    scanf("%d%d", &decimalnum, &base);
    Convert(decimalnum, base);
}