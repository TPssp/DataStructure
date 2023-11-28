#include <stdio.h>
#include <time.h>
clock_t start, stop;
double duration;

void printN(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", i);
    }
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    start = clock();
    printN_slow(n);
    stop = clock();
    duration = ((double)(stop - start)) / CLK_TCK;
    printf("%f", duration);
    return 0;
}