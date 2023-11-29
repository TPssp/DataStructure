#include <stdio.h>
#include <string.h>

#define MAXSIZE 255

typedef char SString[MAXSIZE + 1];

int GetLength(SString S)
{
    int i = 0;
    while (S[i] != '\0')
    {
        i++;
    }
    return i;
}

void InputString(SString &S)
{
    char c;
    int length = GetLength(S);
    for (int i = GetLength(S); i > 0; i--)
    {
        c = S[i - 1];
        S[i] = c;
    }
    S[0] = length;
}

void get_next(SString T, int next[])
{
    int j = 1, k = 0;
    next[1] = 0;
    while (j < T[0])
    {
        if (k == 0 || T[j] == T[k])
        {
            next[++j] = ++k;
        }
        else
        {
            k = next[k];
        }
    }
}

int KMP_Index(SString S, SString T, int pos)
{
    int i = pos, j = 1;
    int next[MAXSIZE + 1] = {0};
    get_next(T, next);
    while (i <= S[0] && j <= T[0])
    {
        if (j == 0||S[i] == T[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j > T[0])
    {
        return i - T[0];
    }
    else
    {
        return 0;
    }
}

int main()
{
    SString S = "asdsdsac";
    SString T = "asd";
    InputString(S);
    InputString(T);
    int pos = KMP_Index(S, T, 1);
    printf("%d\n", pos);

    return 0;
}
