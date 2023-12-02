#include <iostream>
#define MAX_VERTEX_NUM 100
using namespace std;

typedef int VRType;
typedef char VertexType;
typedef enum
{
    DG,
    DN,
    UDG,
    UDN
} GraphKind;

typedef struct ArcNode
{
    int adjvex;
    VRType adj;
    struct ArcNode *nextarc;
} ArcNode;

typedef struct vnode
{
    VertexType data;
    ArcNode *firstarc;
} vonde, adjlist[MAX_VERTEX_NUM];

typedef struct
{
    int vexnum, arcnum, kind;
    adjlist vertices;
} ALGraph;

void Createadjlist(ALGraph &G)
{
    scanf("%d,%d,%d", G.vexnum, &G.arcnum, G.kind);
    int i, j, k;
    double w;
    for (i = 1; i <= G.vexnum; i++)
    {
        G.vertices[i].data = getchar();
        G.vertices[i].firstarc = NULL;
    }
    for (k = 0; k < G.arcnum; k++)
    {
        scanf("%d,%d,%f", &i, &j, &w);
        ArcNode *s = (ArcNode *)malloc(sizeof(ArcNode));
        s->adjvex = j;
        s->adj = w;
        s->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = s;
    }
}