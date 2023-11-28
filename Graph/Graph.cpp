#include <iostream>
#define INFINITY INT_MAX   // 最大值
#define MAX_VERTEX_NUM 100 // 最大顶点个数
typedef int VertexType;
typedef float VRType;
typedef int InfoType;

typedef enum
{
    DG,
    DN,
    UDG,
    UDN
} GraphKind;

typedef struct ArcCell
{                   // 弧的定义
    VRType adj;     // 表示顶点之间的关系
    InfoType *info; // 该弧相关信息的指针
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{                                    // 图的类型定义
    VertexType vexs[MAX_VERTEX_NUM]; // 顶点信息
    AdjMatrix arcs;                  // 弧的信息
    int vexnum, arcnum;              // 顶点数，弧数
    GraphKind kind;                  // 图的种类标志
} MGraph;

bool visited[MAX_VERTEX_NUM] = {false};

void VisitFunc(VertexType v) {      //在 VisitFunc 函数中记录或输出访问的顶点
    printf("%c ", v);
}

void CreateGraph(MGraph &G)
{
    int i, j, k;
    float w;
    scanf("%d %d %d", &G.vexnum, &G.arcnum, &G.kind);

    for (i = 0; i <= G.vexnum; i++) // 建立各个顶点，设顶点为char类型
    {
        G.vexs[i] = getchar();
    }

    for (i = 1; i <= G.vexnum; i++) // 初始化边矩阵
    {
        for (j = 1; j <= G.vexnum; j++)
        {
            G.arcs[i][j].adj = INFINITY;
            G.arcs[i][j].info = NULL;
        }
    }

    for (k = 1; k <= G.arcnum; k++)
    { // 录入各条边
        scanf("%d %d %f", &i, &j, &w);
        G.arcs[i][j].adj = w;
        G.arcs[j][i].adj = w; // 注意对称赋值
    }
}

void PrintGraph(const MGraph &G)
{ // 输出矩阵
    printf("Graph Information:\n");
    printf("Graph Type: %d\n", G.kind);
    printf("Number of Vertices: %d\n", G.vexnum);
    printf("Number of Edges: %d\n", G.arcnum);

    printf("Vertices: ");
    for (int i = 1; i <= G.vexnum; i++)
    {
        printf("%c ", G.vexs[i]);
    }
    printf("\n");

    printf("Adjacency Matrix:\n");
    for (int i = 1; i <= G.vexnum; i++)
    {
        for (int j = 1; j <= G.vexnum; j++)
        {
            if (G.arcs[i][j].adj != INFINITY)
            {
                printf("%c-%c Weight: %.2f\n", G.vexs[i], G.vexs[j], G.arcs[i][j].adj);
            }
            else
            {
                printf("%c-%c Weight: INF\n", G.vexs[i], G.vexs[j]);
            }
        }
    }
}

int FirstAdjVex(const MGraph &G, VertexType v)
{
    int vIndex = -1;
    for (int i = 1; i <= G.vexnum; i++)
    {
        if (G.vexs[i] == v)
        {
            vIndex = i;
            break;
        }
    }

    if (vIndex != -1)
    {
        for (int j = 1; j <= G.vexnum; j++)
        {
            if (G.arcs[vIndex][j].adj != INFINITY)
            {
                return j;
            }
        }
    }

    return -1;
}

int NextAdjVex(const MGraph &G, VertexType v, VertexType w)
{
    int vIndex = -1;
    int wIndex = -1;

    // 查找顶点 v 和 w 在图中的索引
    for (int i = 1; i <= G.vexnum; i++)
    {
        if (G.vexs[i] == v)
        {
            vIndex = i;
        }
        if (G.vexs[i] == w)
        {
            wIndex = i;
        }
    }

    // 如果顶点 v 或 w 不存在于图中，或者w没有是v的邻接点，返回-1
    if (vIndex == -1 || wIndex == -1 || G.arcs[vIndex][wIndex].adj == INFINITY)
    {
        return -1;
    }

    // 查找下一个邻接点
    for (int j = wIndex + 1; j <= G.vexnum; j++)
    {
        if (G.arcs[vIndex][j].adj != INFINITY)
        {
            return j;
        }
    }

    return -1; // 没有找到下一个邻接点
}

void DFS(const MGraph &G, int v)
{
    visited[v] = true;
    printf("%c", G.vexs[v]);
    for (int w = 0; w <= G.vexnum; w++)
    {
        if (G.arcs[v][w].adj != 0 && !visited[w])
        {
            DFS(G, w);
        }
    }
}

int main()
{
    MGraph G;
    CreateGraph(G);
    PrintGraph(G);


    int vIndex = FirstAdjVex(G, '1');
    if (vIndex != -1)
    {
        printf("First Adjacent Vertex to '1': %c\n", G.vexs[vIndex]);
    }
    else
    {
        printf("Vertex 'A' has no adjacent vertices.\n");
    }


    VertexType v = '4'; // 假设要查找与顶点 'A' 相关的下一个邻接点
    VertexType w = '5'; // 假设参考顶点是 'C'

    int nextAdj = NextAdjVex(G, v, w);
    if (nextAdj != -1)
    {
        printf("Next adjacent vertex of %c relative to %c is %c\n", v, w, G.vexs[nextAdj]);
    }
    else
    {
        printf("No next adjacent vertex found for %c relative to %c\n", v, w);
    }

    printf("DFS Traversal: ");

    //判断非连通图时需要使用for循环遍历算法
    // for (int i = 0; i <= G.vexnum; i++) {
    //     if (!visited[i]) {
    //         DFS(G, i);
    //     }
    // }

    DFS(G,1);

    printf("\n");
}