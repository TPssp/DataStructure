#include<stdlib.h>
#include<stdio.h>

#define MAX_VERTEX_NUM 104
#define INFINITY 1000
typedef struct {
	int vex[MAX_VERTEX_NUM];
	float arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum, arcnum;
}MGraph;

void ShortestPath_DIJ(MGraph G, int v0, float* D) {
	int final[MAX_VERTEX_NUM] = { 0 };
	int v;
	for (v = 0; v < G.vexnum; v++) {
		D[v] = G.arcs[v0][v];
	}
	D[v0] = 0;
	final[v0] = 1;
	int i, w;
	float min;
	for (i = 1; i < G.vexnum; i++) {
		min = INFINITY;
		for (w = 0; w < G.vexnum; w++) {
			if(!final[w])
				if (D[w] < min) {
					v = w;
					min = D[w];
				}
		}
		final[v] = 1;
		for (w = 0; w < G.vexnum; w++) {
            if (!final[w] && ((min + G.arcs[v][w]) < D[w]))
            {
                D[w] = min + G.arcs[v][w];
            }
        }
	}
}

int main()
{
    MGraph G;
    scanf("%d %d", &G.vexnum, &G.arcnum);
    int i, j;
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
            G.arcs[i][j] = INFINITY;
        G.vex[i] = i + 1;
    }
    int num1, num2;
    for (i = 0; i < G.arcnum; i++)
    {
        scanf(" %d %d", &num1, &num2);
        G.arcs[num1 - 1][num2 - 1] = 1;
        G.arcs[num2 - 1][num1 - 1] = 1;
    }
    float *D = (float *)malloc(sizeof(float) * G.vexnum);
    for (i = 0; i < G.vexnum; i++)
    {
        int num = 0;
        ShortestPath_DIJ(G, i, D);
        for (j = 0; j < G.vexnum; j++)
            if (D[j] <= 6)
                num++;
        printf("%d: %.2f%%", i + 1, ((float)num / G.vexnum) * 100);
        if (i != G.vexnum - 1)
            printf("\n");
    }
    return 0;
}
