#include <stdio.h>
#include <assert.h>

typedef char SString[];

void get_next(SString T, int next[]) {
    int j = 1, k = 0;
    next[0] = 1;
    while (j < T[0]) {
        if (k == 0 || T[j] == T[k]) {
            next[++j] = ++k;
        } else {
            k = next[k];
        }
    }
}

void test_get_next() {
    SString T = "ababab";
    int next[7] = {0};
    int expected_next[7] = {1, 1, 2, 3, 4, 5, 6};
    get_next(T, next);
    for (int i = 0; i < 7; i++) {
        assert(next[i] == expected_next[i]);
    }
}

int main() {
    test_get_next();
    printf("All tests passed.\n");
    return 0;
}