#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;
#define MAXSIZE 255

typedef unsigned char SString[MAXSIZE + 1];

int Index(SString S, SString T, int pos)
{
    int i = pos, j = 1;
    while (i <= S[0] && j <= T[0])
    {
        if (S[i] == T[j])
        {
            ++i;
            ++j;
        }
        else
        {
            i = i - j + 2;
            j = 1;
        }
    }
    if (j > T[0])
        return i - T[0];
    else
        return 0;
}