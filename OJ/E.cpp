#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 10000

typedef int Status;

typedef struct {
	int i, j;
	int e;
}Triple;
typedef struct {
	Triple data[MAXSIZE];
	int mu, nu, tu;
}TSMatrix;

int main() {
	int i;
	TSMatrix T;
	scanf("%d %d %d", &T.mu, &T.nu, &T.tu);
	for (i = 0; i < T.tu; i++) {
		scanf("%d %d %d", &T.data[i].i, &T.data[i].j, &T.data[i].e);
	}
	TSMatrix M;
	M.nu = T.mu;
	M.mu = T.nu;
	M.tu = T.tu;
	int p = 0,q,r;
	for (r = 1; r <= T.nu; r++) {
		for (q = 0; q <= T.tu; q++) {
			if (T.data[q].j == r) {
				M.data[p].i = T.data[q].j;
				M.data[p].j = T.data[q].i;
				M.data[p].e = T.data[q].e;
				p++;
			}
		}
	}
	printf("%d %d %d", M.mu, M.nu, M.tu);
	printf("\n");
	for (i = 0; i < M.tu; i++) {
		printf("%d %d %d", M.data[i].i, M.data[i].j, M.data[i].e);
		printf("\n");
	}
	return 0;
}