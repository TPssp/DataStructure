#include <stdio.h>
#define MAX_STACK_SIZE 100
#define MAX_ROWS 6
#define MAX_COLS 8
typedef struct
{
    int x;
    int y;
} Position;

int maze[MAX_ROWS][MAX_COLS] = {
    {0, 1, 1, 1, 0, 1, 1, 1},
    {1, 0, 1, 0, 1, 0, 1, 0},
    {0, 1, 0, 0, 1, 1, 1, 1},
    {0, 1, 1, 1, 0, 0, 1, 1},
    {1, 0, 0, 1, 1, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0}};

struct Move
{
    int i;
    int j;
};

struct Move move[8] = {
    {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

typedef struct
{
    Position data[MAX_STACK_SIZE];
    int top;
} MazeStack;

void initStack(MazeStack *stack)
{
    stack->top = -1;
}

int isEmpty(MazeStack *stack)
{
    return stack->top == -1;
}

void push(MazeStack *stack, Position pos)
{
    if (stack->top < MAX_STACK_SIZE - 1)
    {
        stack->data[++stack->top] = pos;
    }
}

Position pop(MazeStack *stack)
{
    Position pos = {-1, -1}; // Invalid position
    if (!isEmpty(stack))
    {
        pos = stack->data[stack->top--];
    }
    return pos;
}

int findPath(int maze[MAX_ROWS][MAX_COLS], MazeStack *stack)
{
    int startRow = 0, startCol = 0;
    int endRow = MAX_ROWS - 1, endCol = MAX_COLS - 1;

    Position startPos = {startRow, startCol};
    Position endPos = {endRow, endCol};

    push(stack, startPos); // 将入口位置入栈

    while (!isEmpty(stack))
    {
        Position currentPos = stack->data[stack->top];

        // 如果当前位置是出口，打印路径并返回
        if (currentPos.x == endPos.x && currentPos.y == endPos.y)
        {
            printf("Found path!\n");

            // 打印路径
            for (int i = 0; i <= stack->top; ++i)
            {
                printf("(%d, %d) ", stack->data[i].x, stack->data[i].y);
            }

            return 1; // 找到路径
        }

        int found = 0; // 标记是否找到可以走的方向

        // 尝试向八个方向移动
        for (int k = 0; k < 8; ++k)
        {
            int nextRow = currentPos.x + move[k].i;
            int nextCol = currentPos.y + move[k].j;

            // 检查是否越界和是否可以走
            if (nextRow >= 0 && nextRow < MAX_ROWS &&
                nextCol >= 0 && nextCol < MAX_COLS &&
                maze[nextRow][nextCol] == 0)
            {
                Position nextPos = {nextRow, nextCol};
                push(stack, nextPos);       // 将新位置入栈
                maze[nextRow][nextCol] = 2; // 标记已走过的位置
                found = 1;                  // 找到了可以走的方向
                break;                      // 只需找到一个方向即可
            }
        }

        // 如果没有找到可以走的方向，退栈
        if (!found)
        {
            pop(stack);
        }
    }

    printf("No path found.\n");
    return 0; // 没有找到路径
}

int main()
{
    MazeStack stack;
    initStack(&stack);

    if (!findPath(maze, &stack))
    {
        printf("No path found.\n");
    }

    return 0;
}
