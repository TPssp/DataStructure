#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 100
#define INFINITY 9999
typedef enum{DG,DN,UDG,UDN}GraphKind;
typedef struct {
    int adj;
} ArcCell;

typedef struct {
    char vexs[MAX_VERTEX_NUM];
    ArcCell arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum;
    int arcnum;
    GraphKind kind;
} MGraph;

// 创建图
void Creategraph(MGraph *G) {
    int i, j, k, u;
    char a, b;
    int w;

    scanf("%d %d %d", &(G->kind), &(G->vexnum), &(G->arcnum));

    for (i = 1; i <= G->vexnum; i++) {
        scanf(" %c", &(G->vexs[i]));
    }

    if (G->kind == 0) {
        for (i = 1; i <= G->vexnum; i++) {
            for (j = 1; j <= G->vexnum; j++) {
                G->arcs[i][j].adj = 0;
            }
        }
        for (k = 1; k <= G->arcnum; k++) {
            scanf(" %c %c", &a, &b);
            for (u = 1; u <= G->vexnum; ++u) {
                if (G->vexs[u] == a) {
                    i = u;
                }
                if (G->vexs[u] == b) {
                    j = u;
                }
            }
            G->arcs[i][j].adj = 1;
        }
    } else if (G->kind == 1) {
        for (i = 1; i <= G->vexnum; i++) {
            for (j = 1; j <= G->vexnum; j++) {
                G->arcs[i][j].adj = INFINITY;
            }
        }
        for (k = 1; k <= G->arcnum; k++) {
            scanf(" %c %c %d", &a, &b, &w);
            for (u = 1; u <= G->vexnum; ++u) {
                if (G->vexs[u] == a) {
                    i = u;
                }
                if (G->vexs[u] == b) {
                    j = u;
                }
            }
            G->arcs[i][j].adj = w;
        }
    } else if (G->kind == 2) {
        for (i = 1; i <= G->vexnum; i++) {
            for (j = 1; j <= G->vexnum; j++) {
                G->arcs[i][j].adj = 0;
            }
        }
        for (k = 1; k <= G->arcnum; k++) {
            scanf(" %c %c", &a, &b);
            for (u = 1; u <= G->vexnum; ++u) {
                if (G->vexs[u] == a) {
                    i = u;
                }
                if (G->vexs[u] == b) {
                    j = u;
                }
            }
            G->arcs[i][j].adj = 1;
            G->arcs[j][i].adj = 1;
        }
    } else {
        for (i = 1; i <= G->vexnum; i++) {
            for (j = 1; j <= G->vexnum; j++) {
                G->arcs[i][j].adj = INFINITY;
            }
        }
        for (k = 1; k <= G->arcnum; k++) {
            scanf(" %c %c %d", &a, &b, &w);
            for (u = 1; u <= G->vexnum; ++u) {
                if (G->vexs[u] == a) {
                    i = u;
                }
                if (G->vexs[u] == b) {
                    j = u;
                }
            }
            G->arcs[i][j].adj = w;
            G->arcs[j][i].adj = w;
        }
    }
}

// 深度优先搜索算法
void DFS(MGraph G, int v, int *visited) {
    visited[v] = 1;
    printf("%c", G.vexs[v]);

    int u;
    for (u = 1; u <= G.vexnum; u++) {
        if (G.arcs[v][u].adj != 0 && !visited[u] && G.arcs[v][u].adj != INFINITY) {
            DFS(G, u, visited);
        }
    }
}

void DFSTraverse(MGraph G, int v0) {
    int i;
    int visited[MAX_VERTEX_NUM];
    for (i = 1; i <= G.vexnum; i++) {
        visited[i] = 0;
    }

    int v = v0 - 1;
    for (i = 1; i <= G.vexnum; i++, v = (v + 1) % G.vexnum) {
        if (!visited[v + 1]) {
            DFS(G, v + 1, visited);
        }
    }
}

int main() {
    MGraph G;
    Creategraph(&G);

    if (G.vexnum != 0) {
        char v;
        scanf(" %c", &v);
        int i;
        for (i = 1; v != G.vexs[i]; i++);
        DFSTraverse(G, i);
    }

    return 0;
}